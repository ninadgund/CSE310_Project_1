
all : preproc encode

preproc : preprocess.cpp
	g++ preprocess.cpp -o preprocess

encode : encode.cpp
	g++ encode.cpp -o encode
