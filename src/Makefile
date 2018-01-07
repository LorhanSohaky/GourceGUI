# The MIT License (MIT)

# Copyright (c) 2016 Lorhan Sohaky

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

FLAGS = -Wall -I./view -I./controller -I./model -I../utils -I../utils/String/src `pkg-config --cflags --libs gtk+-3.0` -o

all: main Main

Main:
	gcc ../obj/*.o $(FLAGS) ../bin/gourceGui.exe

main: Process_creator Gource Call_backs_video_page Video_page Call_backs_other_page Other_page Call_backs_caption_page Caption_page Call_backs_main_menu Main_menu Controller
	gcc -c main.c $(FLAGS) ../obj/main.o

Controller:
	gcc -c ./controller/controller.c $(FLAGS) ../obj/controller.o

Main_menu:
	gcc -c ./view/main_menu.c $(FLAGS) ../obj/main_menu.o

Video_page:
	gcc -c ./view/video_page.c $(FLAGS) ../obj/video_page.o

Caption_page:
	gcc -c ./view/caption_page.c $(FLAGS) ../obj/caption_page.o

Other_page:
	gcc -c ./view/other_page.c $(FLAGS) ../obj/other_page.o

Gource:
	gcc -c ./model/gource.c $(FLAGS) ../obj/gource.o

Process_creator:
	gcc -c ./model/process_creator.c $(FLAGS) ../obj/process_creator.o

Call_backs_main_menu:
	gcc -c ./controller/call_backs_main_menu.c $(FLAGS) ../obj/call_backs_main_menu.o

Call_backs_video_page:
	gcc -c ./controller/call_backs_video_page.c $(FLAGS) ../obj/call_backs_video_page.o

Call_backs_caption_page:
	gcc -c ./controller/call_backs_caption_page.c $(FLAGS) ../obj/call_backs_caption_page.o

Call_backs_other_page:
	gcc -c ./controller/call_backs_other_page.c $(FLAGS) ../obj/call_backs_other_page.o
