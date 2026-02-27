function [pkC] = rotUla(rotAng,ci)
%[pkC] = untitled3(rotAng,ci) Summary of this function goes here
%   Detailed explanation goes here
	%pi = atan(1.0) * 4.0;
	rotAng = rotAng * pi / 180.0;
	xc = cos(ci * pi / 180.0); yc = sin(ci * pi / 180.0);
	num = xc * cos(rotAng) - yc * sin(rotAng);
	den = xc * sin(rotAng) + yc * cos(rotAng);
	pkC = atan2(num, den); 
    pkC = pkC * 180.0 / pi;
end