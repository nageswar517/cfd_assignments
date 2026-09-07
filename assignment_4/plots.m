clc, clearvars, clear;

temp = readmatrix("assignment_4\T.dat");

x_flat = temp(:, 1);
y_flat = temp(:, 2);
T_flat = temp(:, 3);

x_len = length(unique(x_flat));
y_len = length(unique(y_flat));

X = reshape(x_flat, [y_len, x_len]);
Y = reshape(y_flat, [y_len, x_len]);
T = reshape(T_flat, size(X));

figure;
hold on;
plot(X, Y, 'w-');
plot(X', Y', 'w-');
hold off;
title('Grid');
xlabel('X-axis');
ylabel('Y-axis');
axis equal;
exportgraphics(gcf, 'assignment_4\grid.png', 'Resolution', 600);

figure;
pcolor(X, Y, T);
shading flat;
colormap("parula");
colorbar;

title('Temperature colour map');
xlabel('X-Axis');
ylabel('Y-Axis');
axis equal;