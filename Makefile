utils: otherMake
	@cd utils && make
	@cd ..

otherMake:
	@mkdir obj -p
	@mkdir bin -p
