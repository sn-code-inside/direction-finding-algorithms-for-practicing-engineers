% Example system (with noise)
A = [1.02 2.03; 3.04 4.01; 5.00 6.02];
b = [7.03; 8.97; 10.95];

x_tls = tLs(A, b);
x_ls  = inv(A'*A)*A'*b;

disp('TLS solution:'); disp(x_tls);
disp('LS solution:'); disp(x_ls);