clc, clearvars, close all;

% PGS PLOTS
pgs = readmatrix("assignment_6\pgs.dat");

x_flat1 = pgs(:, 1);
y_flat1 = pgs(:, 2);
T_flat1 = pgs(:, 3);

x_unique1 = unique(x_flat1);
y_unique1 = unique(y_flat1);
xlen1 = length(x_unique1);
ylen1 = length(y_unique1);

X1 = reshape(x_flat1,[xlen1, ylen1])';
Y1 = reshape(y_flat1, [xlen1, ylen1])';
T1 = reshape(T_flat1, [xlen1, ylen1])';

figure(Name="Temperature distribution", Color="White");
hold on;

contourf(X1, Y1, T1, 50, 'LineColor', 'none');
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

hold off;
colormap("jet");
c = colorbar;
c.Label.String = "Temperature (T)";

title("Point Gauss Seidel Temperature Distribution");
xlabel("X Coordinate (m)");
ylabel("Y Coordinate (m)");

axis equal;
axis tight;
exportgraphics(gcf, "assignment_6\plots\pgs.png", Resolution=600);

x0 = readmatrix("assignment_6\pgs_x0.dat");
y2 = x0(:, 1);
T2 = x0(:, 2);

figure(Name="Temperature at x=0m", Color="White");
hold on;
plot(y2, T2, LineStyle="-", Color="White");
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

hold off;
title("Point Gauss Seidel Temperature Distribution at x=0m");
xlabel("Y Coordinate (m)");
ylabel("Temperature (K)");

axis tight;
exportgraphics(gcf, "assignment_6\plots\pgs_x0.png", Resolution=600);

x25 = readmatrix("assignment_6\pgs_x25.dat");
y3 = x25(:, 1);
T3 = x25(:, 2);

figure(Name="Temperature at x=0.25m", Color="White");
hold on;
plot(y3, T3, LineStyle="-", Color="White");
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

hold off;
title("Point Gauss Seidel Temperature Distribution at x=0.25m");
xlabel("Y Coordinate (m)");
ylabel("Temperature (K)");

axis tight;
exportgraphics(gcf, "assignment_6\plots\pgs_x25.png", Resolution=600);

x50 = readmatrix("assignment_6\pgs_x50.dat");
y4 = x50(:, 1);
T4 = x50(:, 2);

figure(Name="Temperature at x=0.5m", Color="White");
hold on;
plot(y4, T4, LineStyle="-", Color="White");
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

hold off;
title("Point Gauss Seidel Temperature Distribution at x=0.5m");
xlabel("Y Coordinate (m)");
ylabel("Temperature (K)");

axis tight;
exportgraphics(gcf, "assignment_6\plots\pgs_x50.png", Resolution=600);
