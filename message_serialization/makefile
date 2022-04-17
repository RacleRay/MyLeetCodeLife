server:server.cpp header.cpp message.h header.h jsonser.h jsonser.cpp Protocal.pb.h Protocal.pb.cc serialization.h
	g++ -O2 -std=c++14 -o server server.cpp header.cpp jsonser.cpp Protocal.pb.cc -lpthread -lprotobuf -lboost_serialization -D_PROTO
client:client.cpp header.cpp message.h header.h jsonser.h jsonser.cpp Protocal.pb.h Protocal.pb.cc serialization.h
	g++ -O2 -std=c++14 -o client client.cpp header.cpp jsonser.cpp Protocal.pb.cc -lpthread -lprotobuf -lboost_serialization -D_PROTO
