FLAGS=-O3 --expt-relaxed-constexpr

RM=rm -f

EXEC=mandelbrot_cuda

all: $(EXEC)

$(EXEC):
	nvcc $(EXEC).cu -o $(EXEC) $(FLAGS)
	#$(NVCC) $(EXEC).cu -o $(EXEC).o $(FLAGS)
	#$(NVCC) $(EXEC).o -o $(EXEC) $(FLAGS)

clean:
	$(RM) $(EXEC).o $(EXEC)
