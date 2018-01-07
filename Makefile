utils: otherMake
	@cd utils && make
	@cd ..

otherMake:
	@mkdir obj -p
	@mkdir bin -p

clean:
	rm obj -dr
	rm bin -dr
