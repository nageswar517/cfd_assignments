clc, clearvars, close all;

data1 = readmatrix('jacobi.dat');

% 3. Extract the columns
x_flat1 = data1(:, 1);
y_flat1 = data1(:, 2);
T_flat1 = data1(:, 3);

% 4. Determine grid dimensions dynamically
x_unique1 = unique(x_flat1);
y_unique1 = unique(y_flat1);
x_len1 = length(x_unique1);
y_len1 = length(y_unique1);

% 5. Reshape and Transpose
X1 = reshape(x_flat1, [x_len1, y_len1])';
Y1 = reshape(y_flat1, [x_len1, y_len1])';
T1 = reshape(T_flat1, [x_len1, y_len1])';

% 6. Plot the Temperature Distribution
figure('Name', 'Temperature Distribution', 'Color', 'w');
hold on;

contourf(X1, Y1, T1, 30, 'LineColor', 'none');
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]); 

% Optional: If you want to see your mesh grid lines on top, uncomment the next two lines
% plot(X, Y, '-', 'Color', [0 0 0 0.1]); 
% plot(X', Y', '-', 'Color', [0 0 0 0.1]); 

hold off;

% 7. Styling and formatting
colormap(jet);
c = colorbar;
c.Label.String = 'Temperature (T)';

title('Jacobi Temperature Distribution');
xlabel('X-Coordinate (m)');
ylabel('Y-Coordinate (m)');

% Lock the aspect ratio so the physical lx / ly dimensions aren't distorted
axis equal;
axis tight;
exportgraphics(gcf, 'assignment_5\jacobi.png', Resolution=600);

data2 = readmatrix('pgs.dat');

% 3. Extract the columns
x_flat2 = data2(:, 1);
y_flat2 = data2(:, 2);
T_flat2 = data2(:, 3);

% 4. Determine grid dimensions dynamically
x_unique2 = unique(x_flat2);
y_unique2 = unique(y_flat2);
x_len2 = length(x_unique2);
y_len2 = length(y_unique2);

% 5. Reshape and Transpose
X2 = reshape(x_flat2, [x_len2, y_len2])';
Y2 = reshape(y_flat2, [x_len2, y_len2])';
T2 = reshape(T_flat2, [x_len2, y_len2])';

% 6. Plot the Temperature Distribution
figure('Name', 'Temperature Distribution', 'Color', 'w');
hold on;

contourf(X2, Y2, T2, 30, 'LineColor', 'none');
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]); 

% Optional: If you want to see your mesh grid lines on top, uncomment the next two lines
% plot(X, Y, '-', 'Color', [0 0 0 0.1]); 
% plot(X', Y', '-', 'Color', [0 0 0 0.1]); 

hold off;

% 7. Styling and formatting
colormap(jet);
c = colorbar;
c.Label.String = 'Temperature (T)';

title('Point Gauss Seidel Temperature Distribution');
xlabel('X-Coordinate (m)');
ylabel('Y-Coordinate (m)');

% Lock the aspect ratio so the physical lx / ly dimensions aren't distorted
axis equal;
axis tight;
exportgraphics(gcf, 'assignment_5\pgs.png', Resolution=600);

data3 = readmatrix("assignment_5\y_const_jacobi.dat");
x3 = data3(:, 1);
T3 = data3(:, 2);

figure('Name', "Temperature gradient", "Color", 'w');
hold on;

plot(x3, T3, 'LineStyle', '-', 'Color', 'w');
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

title('Temperature vs X at y=0.5m from Jacobi Method');
xlabel('X-Coordinate (m)');
ylabel('Temperature (K)');

hold off;
exportgraphics(gcf, 'assignment_5\gradient_jacobi.png', Resolution=600);

data4 = readmatrix("assignment_5\y_const_pgs.dat");
x4 = data4(:, 1);
T4 = data4(:, 2);

figure('Name', "Temperature gradient", "Color", 'w');
hold on;

plot(x4, T4, 'LineStyle', '-', 'Color', 'w');
set(gcf, 'Color', [0 0 0]);
set(gca, 'Color', [0 0 0]); 
set(gca, 'XColor', [1 1 1], 'YColor', [1 1 1]);

title('Temperature vs X at y=0.5m from Point Gauss Seidel Method');
xlabel('X-Coordinate (m)');
ylabel('Temperature (K)');

hold off;
exportgraphics(gcf, 'assignment_5\gradient_pgs.png', Resolution=600);