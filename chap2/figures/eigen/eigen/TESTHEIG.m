clc;
clear all;
[SNR Y] = lookMat(5,70);
A = Y*Y'; a = size(A);
%scale = (max(max(abs(A))));
scale = 1.0;
B = A/scale;
Bd = diag(diag(B)); 
Bu = diag(diag(B,1),1);
Bl = diag(diag(B,-1),-1);
Btd = Bd + Bu + Bl;
A = Btd;
[e l Jk]=HEIGmJ(A); [E L]=eig(A);

lkv =l*1.0; Lmat = sort(diag(L)); K = 1:length(Lmat);
subplot(211); plot(K,lkv,'.-r',K,Lmat,'o');grid;
legend('House Holder','Matlab','Location','NorthWest');
subplot(212); plot(Jk,'.-b');grid;

sumE = A*0;
for i = 1:a(1)
    sumE = sumE + L(i,i)*E(:,i)*E(:,i)';
%    sum = sum + l(i,i)*e(:,i)*e(:,i)';
end
sumMyE = A*0;
for i = 1:a(1)
%    sum = sum + L(i,i)*E(:,i)*E(:,i)';
    sumMyE = sumMyE + lkv(i)*e(:,i)*e(:,i)';
end
%sumMyE = scale * sumMyE;
ErE = sumE - A;
ErMyE = sumMyE - A;
Er = [ mean(mean(abs(ErE))) mean(mean(abs(ErMyE)))]
