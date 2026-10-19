clc, clearvars, close all;

data = readmatrix("assignment_7\out_100_10.dat");

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
contourf(X, Y, OMEGA, 50, 'LineColor', 'none');
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
lev = [-1e-10 -1e-7 -1e-5 -1e-4 -1e-3 -1e-2 -3e-2 -5e-2 -7e-2 -9e-2 -1e-1 -1.1e-1];
contour(X, Y, PSI, lev);
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);
hold off;
