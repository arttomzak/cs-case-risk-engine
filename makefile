all:
	cmake -S . -B build -G Ninja	
	cmake --build build
	./build/case_risk_engine.exe