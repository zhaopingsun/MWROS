function y=draw_ppi(az,reso,data)
[radialnum,binnum]=size(data);
x=zeros(radialnum,binnum);
y=x;
r=(1:binnum)*(reso/1000.0);
for i=1:radialnum
    arc=1*(az(i)+90)*pi/180;
    x(i,:)=-1*r*cos(arc);
    y(i,:)=r*sin(arc);
end
  y=pcolor(x,y,data);
%   shading interp
  shading flat
  colorbar('EastOutside');
  hold on;
  
 step=reso/1000.0;
 range=binnum*step;
 for c=step:400*step:range
     a=c*cosd(0:360);
     b=c*sind(0:360);
     plot(a,b,'k-');
      plot(a,b,'y');
 end
hold on;

 a1=range*cosd(0:360);
 b1=range*sind(0:360);
 plot(a1,b1,'k-');
 plot(a1,b1,'y');
 hold on;
 
 step1=30;
 for j=step1:30:360
     m=range*cosd(j);
     n=range*sind(j);
     plot([0 m],[0 n],'k-');
     plot([0 m],[0 n],'y-');
 end
   hold on;
xlabel('X (km)');
ylabel('Y (km)');
set(gca,'color','black')
     
     
 
 
