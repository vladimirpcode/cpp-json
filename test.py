import subprocess
import os
import json
import test_data


for json_obj in test_data.json_objects:
    s = subprocess.run([os.path.abspath(os.curdir) + "/test_app", json.dumps(json_obj)], capture_output=True)
    try:
        json_obj_from_cpp = json.loads(str(s.stdout.decode()))
    except Exception as e:
        print("json from cpp:")
        print(str(s.stdout.decode()))
        print("correct json:")
        print(json.dumps(json_obj))
    if(json_obj_from_cpp != json_obj):
        print("json from cpp:")
        print(json_obj_from_cpp)
        print("correct json:")
        print(json_obj)