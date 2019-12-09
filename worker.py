from subprocess import Popen, PIPE
import os

run = os.system("docker run -it eval-os")
if KeyboardInterrupt:
    terminate = os.system("docker rm $(docker ps -a -f status=exited -q)")

