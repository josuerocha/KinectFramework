################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Calculations.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Filtering.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/IO.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/KinectControl.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Object.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Processing.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Recognition.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Reconstruction.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Registering.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/SegmentationAlgorithms.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Transformations.cpp \
/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Viewer.cpp 

OBJS += \
./src/Calculations.o \
./src/Filtering.o \
./src/IO.o \
./src/KinectControl.o \
./src/Object.o \
./src/Processing.o \
./src/Recognition.o \
./src/Reconstruction.o \
./src/Registering.o \
./src/SegmentationAlgorithms.o \
./src/Transformations.o \
./src/Viewer.o 

CPP_DEPS += \
./src/Calculations.d \
./src/Filtering.d \
./src/IO.d \
./src/KinectControl.d \
./src/Object.d \
./src/Processing.d \
./src/Recognition.d \
./src/Reconstruction.d \
./src/Registering.d \
./src/SegmentationAlgorithms.d \
./src/Transformations.d \
./src/Viewer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Calculations.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Calculations.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Filtering.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Filtering.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/IO.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/IO.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/KinectControl.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/KinectControl.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Object.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Object.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Processing.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Processing.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Recognition.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Recognition.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Reconstruction.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Reconstruction.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Registering.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Registering.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/SegmentationAlgorithms.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/SegmentationAlgorithms.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Transformations.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Transformations.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Viewer.o: /home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2\ -\ Exemplos\ implementação/LIBRARY/src/Viewer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/eigen3 -I/usr/local/include/pcl-1.8 -I/usr/local/include/vtk-7.1 -I/usr/include/ni -I"/home/jr/Dropbox/CEFET-MG/Projetos/IniciacaoCientifica-PCL/2 - Exemplos implementação/LIBRARY/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


