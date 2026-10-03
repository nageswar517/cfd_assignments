clc, clearvars, close all;

data2 = readmatrix('jacobi.dat');

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

title('Jacobi Temperature Distribution');
xlabel('X-Coordinate (m)');
ylabel('Y-Coordinate (m)');

% Lock the aspect ratio so the physical lx / ly dimensions aren't distorted
axis equal;
axis tight;

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