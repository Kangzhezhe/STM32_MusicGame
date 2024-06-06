import os
import sys
import LVGLImage
for path in os.listdir("./pics"):
    file = "./pics/"+path
    print(file)
    sys.argv = ["python.exe", "LVGLImage.py", "--ofmt","BIN","--cf","RGB565","--align","1","--compress","NONE",str(file),"-o",str(path[:-4])]
    LVGLImage.main()