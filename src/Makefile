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

all:Main clean

Main:main.o main_menu.o controller.o
	gcc -Wall -o prog main.o main_menu.o controller.o `pkg-config --cflags --libs gtk+-3.0`

main.o:main.c ./view/main_menu.h ./controller/controller.h
	gcc -c main.c -I./view/ -I./controller/ `pkg-config --cflags --libs gtk+-3.0`

controller.o:./controller/controller.c ./controller/controller.h ./view/main_menu.h
	gcc -c ./controller/controller.c -I./controller/ -I./view/ `pkg-config --cflags --libs gtk+-3.0`

main_menu.o:./view/main_menu.c ./view/main_menu.h
	gcc -c ./view/main_menu.c -I./view/ `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm -rf *.o
