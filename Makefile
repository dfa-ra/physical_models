run:
	cmake -S . -B build
	make -C ./build
	eval ./build/physical_models
	python3 ./drawer/draw.py