clc, clearvars, close all;

% PSOR PLOTS

psor = readmatrix("assignment_6\psor\psor_19.dat");

x_flat5 = psor(:, 1);
y_flat5 = psor(:, 2);
T_flat5 = psor(:, 3);

x_unique5 = unique(x_flat5);
y_unique5 = unique(y_flat5);
xlen5 = length(x_unique5);
ylen5 = length(y_unique5);

X5 = reshape(x_flat5,[xlen5, ylen5])';
Y5 = reshape(y_flat5, [xlen5, ylen5])';
T5 = reshape(T_flat5, [xlen5, ylen5])';

figure(Name="Temperature distribution", Color="White");
hold on;

contourf(X5, Y5, T5, 50, 'LineColor', 'none');
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

hold off;
colormap("jet");
c = colorbar;
c.Label.String = "Temperature (T)";

title("Point Successive Over Relaxation Temperature Distribution");
xlabel("X Coordinate (m)");
ylabel("Y Coordinate (m)");

axis equal;
axis tight;
%exportgraphics(gcf, "assignment_6\plots\psor.png", Resolution=600);

ovi = readmatrix("assignment_6\psor\omega_vs_it.dat");
it = ovi(:, 1);
omega = ovi(:, 2);

figure(Name="Omega vs Iteratioins", Color="White");
hold on;

plot(omega, it, LineStyle="-", Color="White");
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

hold off;
title("Number of Iterations vs Omega");
xlabel("Omega");
ylabel("Number of Iterations");

axis tight;