function phi = mergeLogic(a,b,c)
%[doa] = mergeLogic(doaA,doaB,doaC) Summary of this function goes here
%   Detailed explanation goes here
%a = doaA(:,1)'; b = doaB(:,1)'; c = doaC(:,1)';
n = length(a);
p=1;
for j=1:n
for m=1:n
for k=1:n
    v = [a(j) b(k) c(m)];
    [ang,zone] = map3ula(v);
    if (zone > 0 && p == 1) oldphi = ang; 
        phi(p) = ang; 
        p = p+1; end
    if (zone > 0 && p > 1) 
        if (oldphi ~= ang); oldphi = ang; 
            phi(p) = ang; 
            p=p+1; end 
    end
end
end
end


end