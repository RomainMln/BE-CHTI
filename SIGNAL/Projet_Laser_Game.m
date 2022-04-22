clear all;
close all;
clc;
T=1/5;
Fe=320;
M=T*Fe;
F1P=85;
F3P=95;
F5P=115;
F1=85.0059;
F2=90;
F3=94.9868;
F4=100;
F5=115.0159;
F6=120;
Res=sim('Projet_Laser');
plot(Res.Signal_E)
signal_fft = fft(Res.Signal_E.data);
signal_fft = signal_fft/M;
for k = 1:M/8
    Res.Signal_E.data(k) = 0;
end
hold on;
plot(Res.Signal_E)
hold off;
figure;
aux = linspace(0,M-1,M);
abscisse =aux * 1/T;
stem(abscisse,abs(signal_fft),'gx');
hold on;
signal_fft = fft(Res.Signal_E.data);
signal_fft = signal_fft/M;
stem(abscisse,abs(signal_fft),'ro');
% hold on;
% F1=F1P;
% F3=F3P;
% F5=F5P;
% Res=sim('Projet_Laser');
% signal_fftP = fft(Res.Signal_E.data);
% signal_fftP = signal_fftP/M;
% semilogy(abscisse,abs(signal_fftP),'x');
grid;
% hold off;