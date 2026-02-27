% Author: Kaluri V. Ranga Rao
% Visiting Scholar, Department of Computer Science,
% The Ohio State University
%
% Copyright (c) 2025 Kaluri V. Ranga Rao
% All rights reserved.
%
% This code is part of the material for the book:
% "Direction Finding Algorithms for Practicing Engineers,"
% published by Springer Nature.
%
% This material is intended for academic and research purposes only.
%	function [Z,X,Y]=pdf_y(y,n)	
%   y = randn([1 1000]);
%   [Z,X,Y] = pdf_y(y,40);
%   plot(X,Z,'.-r',X,Y,'.-b');grid
%	Finds the pdf of y specifed
%	by n bins and returns the	
%	range and pdf in X and Y
%	resectively

function [Z,X,Y]=pdf_y(y,n)
    w=0.5;
	l=length(y);
	[N,X]=hist(y,n);
	Y=N/l;
	clear l;
    sig = std(y)*w; mu = mean(y);
    x = (X - mu).*(X - mu); x = x/(2*sig*sig);
    g = 1/( sig*sqrt(2*pi) );
    z = g*exp(-x); Z = z/(sum(z));
	return;