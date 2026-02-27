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
function [sx,f]=spk(x,delt)

%	usage function [sx,f]=spk(x,delt);
%	This finds the spectrum of the given
%	vector x  
%	returns 'sx' spectrum and 'f' the frequency

	n=length(x); 
	frac=log(n)/log(2);
	if ( (frac - fix(frac)) > 0 ) 
        	m=fix(frac)+1; N=2^m;
	else
                N=n; 
        end;
%	w=hamming(n);
%	x1=w.*x';
	sxtemp=fft(x,N); f=linspace(0,0.5,N/2);
	f=f/delt;
	sx=(abs(sxtemp(1:N/2)))/(n/2);
	return
