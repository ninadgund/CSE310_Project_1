
all : preproc encode decode

preproc : preprocess.cpp
	g++ preprocess.cpp -o preprocess

encode : encode.cpp
	g++ encode.cpp -o encode

decode : decode.cpp
	g++ decode.cpp -o decode
