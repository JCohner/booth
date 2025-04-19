
compile:
	@arduino-cli compile --output-dir bin --fqbn arduino:avr:uno \
	--build-property "compiler.cpp.extra_flags=-std=c++14" -v --build-path build .

deploy:
	# can parse `arduino-cli board list` with awk if needed 
	arduino-cli upload --input-file bin/neo_pix.ino.with_bootloader.bin --fqbn arduino:avr:uno -p /dev/ttyACM0 --verbose