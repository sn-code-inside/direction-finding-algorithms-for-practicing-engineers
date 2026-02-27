        clear all;close all;
        theta=0:1:360; theta_rad=theta*pi/180;
        dB3Elev = 20; dB3Azmth = 1.1;
        theta_db=dB3Elev*pi/180; azm_db=dB3Azmth*pi/180;
        sigma_e=(theta_db^2*0.25*log10(exp(1)))/0.3;
        sigma_a=(azm_db^2*0.25*log10(exp(1)))/0.3;
        r1=(exp(-(theta_rad-pi).*(theta_rad-pi)/sigma_e));
        i=0;
        for phi=-2:0.05:2;
            i=i+1; phirad=phi*pi/180; r2=r1*exp(-phirad*phirad/0.00015);
            r3=r2.*cos(theta_rad); delphi = 12*pi/180;
            X(:,i)=(r3*cos(phirad))'; Y(:,i)=(r3*sin(phirad))';
            Z(:,i)=(r2.*sin(theta_rad-delphi))';
        end;
            X(:,i+1)=cos(theta_rad)'; Y(:,i+1)=sin(theta_rad)';
            Z(:,i+1)=0*r1';
        
        meshc(X*180,Y*180,Z*180);
        axis equal;   view(10,30);
        title(' Rotating Fan Beam of Surveilance Radar ','interpreter','latex');
        grid off;
        xlabel(' azimuth plane $\varphi$','interpreter', 'latex');
        subtitle(['$\sigma_e$ ' num2str(dB3Elev,2) '$^\circ$ and $\sigma_{az}$ ' ...
            num2str(dB3Azmth,2) '$^\circ$'],'interpreter', 'latex');
        zlabel('$\theta$','interpreter', 'latex');
        xticks([-180 0 180]); xticklabels({'-180^\circ','0^\circ','180^\circ'});
        yticks([-180 0 180]); yticklabels({'-180^\circ','0^\circ','180^\circ'});
        zticks([0 40]); zticklabels({'0^\circ','40^\circ'});
  % Fan Beam plot
  xa = [130 -170];
  ya = [130  -1];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['Fan Beam $r(\varphi,\theta)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  % axis of rotation
  xa = [0 0];
  ya = [100  0];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['Axis of Rotation'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';


