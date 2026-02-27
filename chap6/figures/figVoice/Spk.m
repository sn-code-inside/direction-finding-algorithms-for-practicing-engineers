
%\begin{verbatim}	
%Digital Signal Processing:A Practitioner's Approach 
%Dr.Kaluri Venkata Ranga Rao ,kaluri@ieee.org
%	usage function [sx,f]=spk(x,delt);
%	This finds the spectrum of the given
%	vector x  
%	returns 'sx' spectrum and 'f' the frequency
%	in dir e:\matlab\toolbox\rf\spk.m
function [sx,phix,f]=spk(x,delt)


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
	phix=(angle(sxtemp(1:N/2)))*180/pi;
	return
%\end{verbatim}