<< EOF
g++ resonanceType.cpp particleType.cpp particle.cpp simulation.cpp `root-config --cflags --libs`
./a.out
g++ analysis.cpp `root-config --cflags --libs`
./a.out
EOF