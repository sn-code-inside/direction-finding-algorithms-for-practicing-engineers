function [] = labelUlaPhase(At,dbyL,theta)
%[] = labelUlaPhase(At) Summary of this function goes here
%   Detailed explanation goes here
    phi = 360*dbyL*sind(theta);
    x1 = At(1,:); x2 = At(2,:); x3 = At(3,:);
    x4 = At(4,:); x5 = At(5,:);

    subplot(221); plot(x1,x2,'.-r');grid;
    title(['$\frac{d}{\lambda}=$ ' num2str(dbyL,2) '; $\theta$ =' ...
        num2str(theta,2) '$^o$; $\varphi$ = ' ...
        num2str(phi,4) '$^o$'],'interpreter','latex')
    xlabel('$\tilde{v}_k$','interpreter','latex'); 
    ylabel('$\tilde{v}_k^{\varphi}$','interpreter','latex');

    subplot(222); plot(x1,x3,'.-b');grid;
    title(['$\frac{d}{\lambda}=$ ' num2str(dbyL,2) '; $\theta$ =' ...
        num2str(theta,2) '$^o$; $\varphi$ = ' ...
        num2str(2*phi,4) '$^o$'],'interpreter','latex')    
    xlabel('$\tilde{v}_k$','interpreter','latex'); 
    ylabel('$\tilde{v}_k^{2\varphi}$','interpreter','latex');
    
    subplot(223); plot(x1,x4,'.-k');grid;
    title(['$\frac{d}{\lambda}=$ ' num2str(dbyL,2) '; $\theta$ =' ...
        num2str(theta,2) '$^o$; $\varphi$ = ' ...
        num2str(3*phi,4) '$^o$'],'interpreter','latex') 
    xlabel('$\tilde{v}_k$','interpreter','latex'); 
    ylabel('$\tilde{v}_k^{3\varphi}$','interpreter','latex');

    subplot(224); plot(x1,x5,'.-c');grid;
    title(['$\frac{d}{\lambda}=$ ' num2str(dbyL,2) '; $\theta$ =' ...
        num2str(theta,2) '$^o$; $\varphi$ = ' ...
        num2str(4*phi,4) '$^o$'],'interpreter','latex') 
    xlabel('$\tilde{v}_k$','interpreter','latex'); 
    ylabel('$\tilde{v}_k^{4\varphi}$','interpreter','latex');
end