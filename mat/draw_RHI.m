function draw_RHI(el,reso,data)    
[elnum,bnum]=size(data);
    r=(1:bnum)*reso/1000; 
    for i=1:elnum
        eang=el(i);
        x(i,:)=r*cosd(eang);
        y(i,:)=r*sind(eang);
    end
    pcolor(x,y,data);
    shading flat
    colorbar('EastOutside');
    hold on;
    xlabel('Range /Km');
    ylabel('Height /Km'); 
%     ylim([0 21]);
%    set(gca,'Ytick',[0:5:20]);
    grid on;