CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = bin/main
SRCS = DataAnalyzer.cpp FileReader.cpp DataProcessor.cpp

$(TARGET): $(SRCS) | bin
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

bin:
	mkdir -p bin

clean:
	rm -rf bin
