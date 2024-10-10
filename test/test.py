import subprocess
import os
import json
import test_data


success_counter = 0
for json_obj in test_data.json_objects:
    s = subprocess.run([os.path.dirname(__file__) + "/test_with_python", json.dumps(json_obj)], capture_output=True)
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
    success_counter += 1
print(f"{success_counter} из {len(test_data.json_objects)}")