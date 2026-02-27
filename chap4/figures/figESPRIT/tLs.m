function x_tls = tLs(A, b)
%x_tls = total_least_squares(A, b) Summary of this function goes here
%   Detailed explanation goes here
    % Check dimensions
    [m, n] = size(A);
    if length(b) ~= m
        error('A and b must have the same number of rows');
    end

    % Form the augmented matrix
    C = [A, b];

    % Compute the SVD
    [~, ~, V] = svd(C, 'econ');

    % Extract the last column of V (associated with smallest singular value)
    v = V(:, end);

    % Split into parts
    v1 = v(1:n);
    v_last = v(end);

    % Check for degenerate case
    if abs(v_last) < eps
        error('TLS solution is undefined: the last component of v is zero.');
    end

    % Compute the TLS solution
    x_tls = -v1 / v_last;
end
