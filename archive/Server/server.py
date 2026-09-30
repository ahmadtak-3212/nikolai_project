"""
Data:
File: Nikolai.py
Description:
"""

import sqlite3
import datetime
import os, sys
from bokeh.plotting import figure, show
from bokeh.embed import components
import json

DATABASE_FILE_DIR = "/var/jail/home/team73/Server/dbs/"
DATABASE_FILE = "nikolai.db"
DATABASE_PATH = DATABASE_FILE_DIR + DATABASE_FILE

def insert_sensor_db(current, temperature, username):
    conn = sqlite3.connect(DATABASE_PATH)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS nikolai_data (time timestamp, current real, temperature real, text user);''')
    now = datetime.datetime.now()
    c.execute('''INSERT into nikolai_data (time, current, temperature, user) VALUES (?,?,?,?);''',(now, current, temperature, username))
    conn.commit()
    conn.close()
    return (now, current, temperature, username)

def insert_user_db(user, password):
    conn = sqlite3.connect(DATABASE_PATH)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (time timestamp, user text, password text);''')
    c.execute('''INSERT into users VALUES (?,?,?);''',(datetime.datetime.now(), user, password))
    conn.commit()
    conn.close()
    return True

def insert_settings_db(user, power_lvl, curr_thresh, temp_thresh):
    conn = sqlite3.connect(DATABASE_PATH)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS settings (time timestamp, user text, power_lvl real, curr_thresh real, temp_thresh real);''')
    all = c.execute('''SELECT * FROM settings WHERE user = ?''', (user,)).fetchall()
    if len(all) == 0:
        c.execute('''INSERT INTO settings VALUES (?, ?, ?, ?, ?);''', (datetime.datetime.now(), user, None, curr_thresh, temp_thresh))
        conn.commit()
        conn.close()
        return f'{power_lvl}\n{curr_thresh}\n{temp_thresh}'
    if curr_thresh is not None:
        c.execute('''UPDATE settings SET curr_thresh = ? WHERE user = ?''', (curr_thresh, user))
    if temp_thresh is not None:
        c.execute('''UPDATE settings SET temp_thresh = ? WHERE user = ?''', (temp_thresh, user))
    conn.commit()
    conn.close()
    return f'{power_lvl}\n{curr_thresh}\n{temp_thresh}'

def select_db():
    conn = sqlite3.connect(DATABASE_PATH)
    c = conn.cursor()
    states = c.execute('''SELECT * FROM nikolai_data ORDER BY time DESC;''').fetchall()
    conn.commit()
    conn.close()
    return states

def get_plot_data(username, time_start, time_end):
    curr_data = []
    temp_data = []
    timestamps = []
    all_data  = []
    with sqlite3.connect(DATABASE_PATH) as c:
        all_data = c.execute('''SELECT current, temperature, time FROM nikolai_data WHERE user = ? AND time > ? AND time < ? ORDER by time ASC;''',(username, time_start, time_end)).fetchall()
        for curr, temp, time in all_data:
            curr_data.append(curr)
            temp_data.append(temp)
            timestamps.append(datetime.datetime.strptime(time,'%Y-%m-%d %H:%M:%S.%f'))

    if not timestamps: return "No data found that matches user."

    p = figure(title=f"Temperature over time for user {username}", x_axis_label="Time", x_axis_type='datetime', y_axis_label="Temperature (in deg C)")
    p.line(timestamps, temp_data)
    q = figure(title=f"Current over time for user {username}", x_axis_label="Time", x_axis_type='datetime', y_axis_label="Current (in A)")
    q.line(timestamps, curr_data)
    script, (div1, div2) = components((p, q))
    return f'''<!DOCTYPE html>
<html> <script src="https://cdn.bokeh.org/bokeh/release/bokeh-2.4.0.min.js"></script>
    <body>
        {div1}
        {div2}
    </body>
    {script}
</html>
'''

def request_handler(request):
    """
    POSTs requests here
    format: form:
                current
                temperature
                user
                power_lvl
                curr_thresh
                temp_thresh
    """
    if request['method'] == 'POST':
        if 'Uname' not in request['form']:
            return "Must include Uname in body to POST data"
        if 'Pass' not in request['form']:
            return "Must include Pass in body for authentication"
        username = request['form']['Uname']
        password = request['form']['Pass']
        with sqlite3.connect(DATABASE_PATH) as c:
            user_search_res = c.execute('''SELECT password from users WHERE user = ?''', (username,)).fetchall()
            if len(user_search_res) == 0:
                insert_user_db(username, password)
            elif user_search_res[0][0] != password:
                return "Authentication error. Shutting down."
        # Successfully authenticated
        current = None
        temperature = None
        curr_thresh = None
        temp_thresh = None
        try:    current = float(request['form']['current'])
        except: pass
        try:    curr_thresh = float(request['form']['curr_thresh'])
        except: pass
        try:    temperature = float(request['form']['temperature'])
        except: pass
        try:    temp_thresh = float(request['form']['temp_thresh'])
        except: pass
        if curr_thresh is not None or temp_thresh is not None:
            return insert_settings_db(username, None, curr_thresh, temp_thresh)
        return insert_sensor_db(current, temperature, username)
    elif request['method'] == 'GET':
        if 'visualize' in request['args'] and request['values']['visualize'] == 'true':
            username = None

            time_end = datetime.datetime.now()
            time_start = datetime.datetime.now() - datetime.timedelta(days=10)
            if 'time_start' in request['args']:
                time_start = datetime.datetime.strptime(request['values']['time_start'], "%m/%d/%Y %H:%M:%S")
            if 'time_end' in request['args']:
                time_end = datetime.datetime.strptime(request['values']['time_end'], "%m/%d/%Y %H:%M:%S")

            try:
                username = request['values']['Uname']
            except KeyError:
                return "No username provided. Shutting down."
            return get_plot_data(username, time_start, time_end)
        elif 'settings' in request['args'] and request['values']['settings'] == 'true':
            username = None
            try: username = request['values']['Uname']
            except KeyError: return "No username provided. Shutting down."
            res = "No such user found"
            with sqlite3.connect(DATABASE_PATH) as c:
                res = c.execute(''' SELECT * from settings where user = ? ORDER BY time''', (username,)).fetchone()
                if res:
                    curr_th = res[3]
                    temp_th = res[4]
                    res = {}
                    res["user"] = username
                    res["curr_thresh"] = curr_th
                    res["temp_thresh"] = temp_th
            return json.dumps(res)

        if len(request['args']) == 0:
            conn = sqlite3.connect(DATABASE_PATH)
            c = conn.cursor()
            date_dt = [str(d[0]) for d in c.execute('''SELECT time FROM nikolai_data;''').fetchall()]
            temp_dt = [float(t[0] if t[0] != None else 0) for t in c.execute('''SELECT temperature FROM nikolai_data ORDER by time ASC;''').fetchall()]
            curr_dt = [float(c[0] if c[0] != None else 0) for c in c.execute('''SELECT current FROM nikolai_data ORDER by time ASC;''').fetchall()]
            conn.commit()
            conn.close()
            return json.dumps({"dts" : date_dt, "temp" : temp_dt, "curr" : curr_dt})
        elif len(request['args']) == 2:
            # try:
            username = request['values']['Uname']
            password = request['values']['Pass']
            with sqlite3.connect(DATABASE_PATH) as c:
                c.execute('''CREATE TABLE IF NOT EXISTS users (time timestamp, user text, password text);''')
                check_pass = c.execute('''SELECT password FROM users WHERE user=?;''', (username,)).fetchone()
            # return (username, password, check_pass)
            if check_pass and password == check_pass[0]:
                valid_login = True
            else:
                valid_login = False
            if not check_pass:
                insert_user_db(username, password)
            # except:
            #     valid_login = False
            return json.dumps({'valid' : valid_login})

if __name__ == "__main__":
    print("NIKOLAI SERVER")
