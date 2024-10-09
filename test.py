import subprocess
import os

json_str = """
{
    "a": 1,
    "b": {
        "c": 2,
        "d": 3
    },
    "c": [
        1,
        2,
        3
    ]
}
"""
print(json_str)
s = subprocess.run([os.path.abspath(os.curdir) + "/test_app", json_str], capture_output=True)
print(str(s.stdout.decode()))