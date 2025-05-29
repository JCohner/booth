SHELL:=/bin/bash
VERSION=0x03

compile:
	@arduino-cli compile --output-dir bin --fqbn arduino:samd:nano_33_iot \
	--build-property "compiler.cpp.extra_flags=-std=c++14" -v --build-path build .

deploy:
	# can parse `arduino-cli board list` with awk if needed 
	arduino-cli upload --input-file bin/booth_controller.ino.bin --fqbn arduino:samd:nano_33_iot  -p /dev/ttyACM1 --verbose

gen_rectangle_code:
	@source venv/bin/activate && python3 rect_gen.py