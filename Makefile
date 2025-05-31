SHELL:=/bin/bash
VERSION=0x03

compile:
	# compile primary
	source venv/bin/activate && python3 rect_gen.py "booth_controller/" 0 29
	@arduino-cli compile --output-dir bin/primary_bin --fqbn arduino:samd:nano_33_iot \
	--build-property "compiler.cpp.extra_flags=-std=c++14" -v --build-path build/primary_build booth_controller/

	source venv/bin/activate && python3 rect_gen.py "booth_controller/" 29 49
	@arduino-cli compile --output-dir bin/secondary_bin --fqbn arduino:samd:nano_33_iot \
	--build-property "compiler.cpp.extra_flags=-std=c++14" -v --build-path build/secondary_build booth_controller/

deploy_primary:
	# can parse `arduino-cli board list` with awk if needed 
	arduino-cli upload --input-file bin/primary_bin/booth_controller.ino.bin --fqbn arduino:samd:nano_33_iot  -p /dev/ttyACM0 --verbose

deploy_secondary:
	# can parse `arduino-cli board list` with awk if needed 
	arduino-cli upload --input-file bin/secondary_bin/booth_controller.ino.bin --fqbn arduino:samd:nano_33_iot  -p /dev/ttyACM0 --verbose