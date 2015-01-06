%code to read sa base data file by Li ZhaoMing
clc
clear all
close all
fclose all


%-------读取数据文件--------------
[FileName,PathName,FilterIndex] = uigetfile('*.*');
FidRead=fopen([PathName,'\',FileName],'rb');
replay=input('您想画的那个仰角的PPI图，请选择1 3 5 6 7 8 9 10 11：','s');%对应角度为0.5,1.5,2.4,3.4,4.3,6.0,9.9,14.6,19.5
Ei_input= str2num(replay);

%-----读取数据文件-----------------
I_jd=0;     %设定一个全局函数，用于记录一个仰角上有多少个方位角
for Index=1:4044
    temp1=fread(FidRead,7,'uint16');		%保留
    RadarStatus=fread(FidRead,1,'uint16');			 	%1 - 表示为雷达数据
    temp2=fread(FidRead,6,'uint16');			 	%保留
    mSeconds=fread(FidRead,2,'uint16');			 	%径向数据收集时间
    JulianDate=fread(FidRead,1,'uint16');			 	%从1970/1/1起的日期
    URange=fread(FidRead,1,'uint16');				 	%不模糊距离
    Az=fread(FidRead,1,'uint16')/8*180/4096;			 	%方位角度
    RadialNumber=fread(FidRead,1,'uint16');			 	%径向数据序号
    RadialStatus=fread(FidRead,1,'uint16');			 	%径向数据状态
    El=fread(FidRead,1,'uint16')/8*180/4096;				 	%仰角
    ElNumber=fread(FidRead,1,'uint16');			 	%体扫内的仰角编号
    RangeToFirstGateOfRef=fread(FidRead,1,'uint16');			%第一个反射率数据表示的实际距离(m)
    RangeToFirstGateOfDop=fread(FidRead,1,'uint16');			%第一个多普勒数据表示的实际距离(m)
    GateSizeOfReflectivity=fread(FidRead,1,'uint16');			%反射率数据的距离库长(m)
    GateSizeOfDoppler=fread(FidRead,1,'uint16');		 	%多普勒数据的距离库长(m)
    GatesNumberOfReflectivity=fread(FidRead,1,'uint16');		%反射率数据的距离库数
    GatesNumberOfDoppler=fread(FidRead,1,'uint16');			%多普勒数据的距离库数
    CutSectorNumber=fread(FidRead,1,'uint16'); 		 	%扇区号
    CalibrationConst=fread(FidRead,2,'uint16'); 		 	%标定常数
    PtrOfReflectivity=fread(FidRead,1,'uint16');		 	%反射率数据指针
    PtrOfVelocity=fread(FidRead,1,'uint16');			 	%速度数据指针
    PtrOfSpectrumWidth=fread(FidRead,1,'uint16');		 	%谱宽数据指针
    ResolutionOfVelocity=fread(FidRead,1,'uint16');			%多普勒速度分辨率
    VcpNumber=fread(FidRead,1,'uint16');		    	%体扫号
    temp4=fread(FidRead,4,'uint16');			    	%保留
    PtrOfArcReflectivity=fread(FidRead,1,'uint16');		%反射率数据指针
    PtrOfArcVelocity=fread(FidRead,1,'uint16');		    	%速度数据指针
    PtrOfArcWidth=fread(FidRead,1,'uint16');			    	%谱宽数据指针
    Nyquist=fread(FidRead,1,'uint16');			    	%不模糊速度
%     temp46=fread(FidRead,1,'uint16');                                 %保留
%     temp47=fread(FidRead,1,'uint16');                                 %保留
%     temp48=fread(FidRead,1,'uint16');                                 %保留
%     CircleTotal=fread(FidRead,1,'uint16');			      	%仰角数
    temp5=fread(FidRead,38,'uint8');%保留
    R=fread(FidRead,460,'uint8');             %129－588 共460字节反射率数据
    V=fread(FidRead,920,'uint8');             %589－1508 共920字节速度数据
    W=fread(FidRead,920,'uint8');             %1509－2428 共920字节谱宽数据
    temp6=fread(FidRead,2,'uint16');		  %保留
              
    if  length(R)==0
        break  
    end
    %------判断是否属于这个仰角范围内------------
    if ElNumber==Ei_input
        
        dBZ=R/2-33;
        VV=V/2-64.5;
        WW=W/2-64.5;
        %-----数据挑选处理-------
        I_jd=I_jd+1;
        N_Ei(I_jd)=El;
        N_angle(I_jd)=Az;
        N_radius(I_jd,:)=dBZ;
        V_radius(I_jd,:)=VV;
        W_radius(I_jd,:)=WW;
    end
end

figure(1)
for i=1:length(N_angle)
    for j=1:460                             %GatesNumberOfReflectivity
        X11(i,j)=j*sin(N_angle(i)/180*pi);
        Y11(i,j)=j*cos(N_angle(i)/180*pi);
    end
end

R=300;
for r = (R/3):(R/3):R
    alpha=0:pi/50:2*pi;%角度[0,2*pi]
    x=r*cos(alpha);
    y=r*sin(alpha);
    plot(x,y,'-k')
    axis square
    hold on
end

%画射线
for i = (pi/6):(pi/6):pi;
    x = [-R*sin(i),R*sin(i)];
    y = [-R*cos(i),R*cos(i)];
    plot(x,y,'-k');
    hold on
end

load Z_color
colormap(b)
caxis([-10,70]);
pcolor(X11,Y11,N_radius);
shading interp;
xlim([-240 240]);
ylim([-240 240]);
axis([-300 300 -300 300])
colorbar('EastOutside');
set(gca,'XTickLabel',str2num(get(gca,'XTickLabel'))*0.5);
set(gca,'YTickLabel',str2num(get(gca,'YTickLabel'))*0.5);
colorbar('EastOutside');
caxis([-10,70]);
colorbar('ytick',[-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65],'yticklabel',{'-5','0','5','10','15','20','25','30','35','40','45','50','55','60','65'});
% colorbar('ytick',[5,10,15,20,25,30,35,40,45,50,55,60,65,70,75],'yticklabel',{'5','10','15','20','25','30','35','40','45','50','55','60','65','70','75'});
% xlabel('距离(km)')
% ylabel('距离(km)')
xlabel('km')
ylabel('km')
% title('S波段雷达观测的反射率因子（常州）');
% title('Observed reflectivity of LWS','FontSize',13);
axis square

% hold on
% plot(0,0,'r+','markersize',10,'LineWidth',2)
% plot(105*sin(276.5*pi/180),105*cos(276.5*pi/180),'r+','markersize',10,'LineWidth',2)
% % plot(175*sin(259*pi/180),175*cos(259*pi/180),'r+','markersize',10,'LineWidth',2)
% plot(175*sin(259*pi/180),175*cos(259*pi/180),'r+','markersize',10,'LineWidth',2)
% sita=0:pi/1000:2*pi;
% plot(120*cos(sita)+105*sin(276.5*pi/180),120*sin(sita)+105*cos(276.5*pi/180),'b','markersize',10,'LineWidth',1); %半径为r的圆,x0,y0为原点坐标
% plot(120*cos(sita)+175*sin(259*pi/180),120*sin(sita)+175*cos(259*pi/180),'b','markersize',10,'LineWidth',1);
% plot(112*sin(122.05*pi/180),112*cos(122.05*pi/180),'r+','markersize',10,'LineWidth',1.5)
% plot(103*sin(163.94*pi/180),103*cos(163.94*pi/180),'r+','markersize',10,'LineWidth',1.5)
% plot(27*sin(162.94*pi/180),27*cos(162.94*pi/180),'r+','markersize',10,'LineWidth',1.5)
% sita=0:pi/1000:2*pi;
% plot(120*cos(sita)+112*sin(122.05*pi/180),120*sin(sita)+112*cos(122.05*pi/180),'k','markersize',10,'LineWidth',1.5); %半径为r的圆,x0,y0为原点坐标
% plot(120*cos(sita)+103*sin(163.94*pi/180),120*sin(sita)+103*cos(163.94*pi/180),'k','markersize',10,'LineWidth',1.5);
% plot(120*cos(sita)+27*sin(162.94*pi/180),120*sin(sita)+27*cos(162.94*pi/180),'k','markersize',10,'LineWidth',1.5);
% text(-220,220,'(b)','FontSize',13)

figure(2)
for i=1:length(N_angle)
    for j=1:920                             %GatesNumberOfReflectivity
        X22(i,j)=j*sin(N_angle(i)/180*pi);
        Y22(i,j)=j*cos(N_angle(i)/180*pi);
    end
end

R=300;
for r = (R/3):(R/3):R
    alpha=0:pi/50:2*pi;%角度[0,2*pi]
    x=r*cos(alpha);
    y=r*sin(alpha);
    plot(x,y,'-k')
    axis square
    hold on
end

%画射线
for i = (pi/6):(pi/6):pi;
    x = [-R*sin(i),R*sin(i)];
    y = [-R*cos(i),R*cos(i)];
    plot(x,y,'-k');
    hold on
end

load Z_color
colormap(b)
caxis([-10,70]);
pcolor(X22,Y22,V_radius);
shading interp;
xlim([-240 240]);
ylim([-240 240]);
axis([-300 300 -300 300])
colorbar('EastOutside');
set(gca,'XTickLabel',str2num(get(gca,'XTickLabel'))*0.5);
set(gca,'YTickLabel',str2num(get(gca,'YTickLabel'))*0.5);
colorbar('EastOutside');
caxis([-10,70]);

figure(3)
for i=1:length(N_angle)
    for j=1:920                           %GatesNumberOfReflectivity
        X33(i,j)=j*sin(N_angle(i)/180*pi);
        Y33(i,j)=j*cos(N_angle(i)/180*pi);
    end
end

R=300;
for r = (R/3):(R/3):R
    alpha=0:pi/50:2*pi;%角度[0,2*pi]
    x=r*cos(alpha);
    y=r*sin(alpha);
    plot(x,y,'-k')
    axis square
    hold on
end

%画射线
for i = (pi/6):(pi/6):pi;
    x = [-R*sin(i),R*sin(i)];
    y = [-R*cos(i),R*cos(i)];
    plot(x,y,'-k');
    hold on
end

load Z_color
colormap(b)
caxis([-10,70]);
pcolor(X33,Y33,W_radius);
shading interp;
xlim([-240 240]);
ylim([-240 240]);
axis([-300 300 -300 300])
colorbar('EastOutside');
set(gca,'XTickLabel',str2num(get(gca,'XTickLabel'))*0.5);
set(gca,'YTickLabel',str2num(get(gca,'YTickLabel'))*0.5);
colorbar('EastOutside');
caxis([-10,70]);











