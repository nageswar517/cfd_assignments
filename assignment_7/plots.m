clc, clearvars, close all;

data = readmatrix("assignment_7\out_400_100.dat");

x_flat = data(:, 1);
y_flat = data(:, 2);
psi_flat = data(:, 3);
omega_flat = data(:, 4);
u_flat = data(:, 5);
v_flat = data(:, 6);

x_unique = unique(x_flat);
y_unique = unique(y_flat);
x_len = length(x_unique);
y_len = length(y_unique);

X = reshape(x_flat, [x_len, y_len])';
Y = reshape(y_flat, [x_len, y_len])';
PSI = reshape(psi_flat, [x_len, y_len])';
OMEGA = reshape(omega_flat, [x_len, y_len])';
U = reshape(u_flat, [x_len, y_len])';
V = reshape(v_flat, [x_len, y_len])';

figure(Name="Vorticity Field", Color="White");
hold on;
lev = [-50 -20 -10 -5 -3 -2.5 -2 -1.5 -1 -0.5 0 0.5 1 2 3 5 10 20 50];
% contourf(X, Y, OMEGA, 'LineColor', 'none');
contourf(X, Y, OMEGA, lev, 'LineColor', 'none');
clim([-5 5]);
% contourf(X, Y, OMEGA, 50, 'LineColor', 'none');
%pcolor(X, Y, OMEGA);
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);
hold off;

colormap("jet");
c = colorbar;
c.Label.String = "Vorticity (1/s)";

title("Vorticity field");
xlabel("X Coordinate (m)");
ylabel("Y Coordinate (m)");

axis equal tight;

figure(Name="Streamlines", Color="White");
hold on;
lev_psi = [-0.1175 -0.11 -0.1 -0.09 -0.07 -0.05 -0.03 -0.01 -1e-4 -1e-5 -1e-6 1e-8 1e-7 1e-6 1e-5 1e-4 5e-4 1e-3 2e-3 3e-3];
contour(X, Y, PSI, lev_psi);
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);
hold off;

title("Streamlines");
xlabel("X Coordinate (m)");
ylabel("Y Coordinate (m)");

axis equal tight;

figure(Name="Velocity Vectors", Color="White");
skip = 10;
idx_y = 1:skip:y_len;
idx_x = 1:skip:x_len;
hold on;

quiver(X(idx_y,idx_x), Y(idx_y,idx_x), U(idx_y,idx_x), V(idx_y,idx_x), 3);
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

hold off;

title("Velocity Vectors");
xlabel("X Coordinate (m)");
ylabel("Y Coordinate (m)");
axis equal tight;
