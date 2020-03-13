close all;
clear;

data = load('line.txt');
numlines = length(data) / 360;

figure;
hold on;
for i = 1:numlines
    plot(data(1+i*360-360 : i*360,1), data(1+i*360-360 : i*360,2), 'color', [rand,rand,rand]);
end
hold off;
