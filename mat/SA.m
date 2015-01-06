%code to read sa base data file by Li ZhaoMing
clc
clear all
close all
fclose all


%-------��ȡ�����ļ�--------------
[FileName,PathName,FilterIndex] = uigetfile('*.*');
FidRead=fopen([PathName,'\',FileName],'rb');
replay=input('���뻭���Ǹ����ǵ�PPIͼ����ѡ��1 3 5 6 7 8 9 10 11��','s');%��Ӧ�Ƕ�Ϊ0.5,1.5,2.4,3.4,4.3,6.0,9.9,14.6,19.5
Ei_input= str2num(replay);

%-----��ȡ�����ļ�-----------------
I_jd=0;     %�趨һ��ȫ�ֺ��������ڼ�¼һ���������ж��ٸ���λ��
for Index=1:4044
    temp1=fread(FidRead,7,'uint16');		%����
    RadarStatus=fread(FidRead,1,'uint16');			 	%1 - ��ʾΪ�״�����
    temp2=fread(FidRead,6,'uint16');			 	%����
    mSeconds=fread(FidRead,2,'uint16');			 	%���������ռ�ʱ��
    JulianDate=fread(FidRead,1,'uint16');			 	%��1970/1/1�������
    URange=fread(FidRead,1,'uint16');				 	%��ģ������
    Az=fread(FidRead,1,'uint16')/8*180/4096;			 	%��λ�Ƕ�
    RadialNumber=fread(FidRead,1,'uint16');			 	%�����������
    RadialStatus=fread(FidRead,1,'uint16');			 	%��������״̬
    El=fread(FidRead,1,'uint16')/8*180/4096;				 	%����
    ElNumber=fread(FidRead,1,'uint16');			 	%��ɨ�ڵ����Ǳ��
    RangeToFirstGateOfRef=fread(FidRead,1,'uint16');			%��һ�����������ݱ�ʾ��ʵ�ʾ���(m)
    RangeToFirstGateOfDop=fread(FidRead,1,'uint16');			%��һ�����������ݱ�ʾ��ʵ�ʾ���(m)
    GateSizeOfReflectivity=fread(FidRead,1,'uint16');			%���������ݵľ���ⳤ(m)
    GateSizeOfDoppler=fread(FidRead,1,'uint16');		 	%���������ݵľ���ⳤ(m)
    GatesNumberOfReflectivity=fread(FidRead,1,'uint16');		%���������ݵľ������
    GatesNumberOfDoppler=fread(FidRead,1,'uint16');			%���������ݵľ������
    CutSectorNumber=fread(FidRead,1,'uint16'); 		 	%������
    CalibrationConst=fread(FidRead,2,'uint16'); 		 	%�궨����
    PtrOfReflectivity=fread(FidRead,1,'uint16');		 	%����������ָ��
    PtrOfVelocity=fread(FidRead,1,'uint16');			 	%�ٶ�����ָ��
    PtrOfSpectrumWidth=fread(FidRead,1,'uint16');		 	%�׿�����ָ��
    ResolutionOfVelocity=fread(FidRead,1,'uint16');			%�������ٶȷֱ���
    VcpNumber=fread(FidRead,1,'uint16');		    	%��ɨ��
    temp4=fread(FidRead,4,'uint16');			    	%����
    PtrOfArcReflectivity=fread(FidRead,1,'uint16');		%����������ָ��
    PtrOfArcVelocity=fread(FidRead,1,'uint16');		    	%�ٶ�����ָ��
    PtrOfArcWidth=fread(FidRead,1,'uint16');			    	%�׿�����ָ��
    Nyquist=fread(FidRead,1,'uint16');			    	%��ģ���ٶ�
%     temp46=fread(FidRead,1,'uint16');                                 %����
%     temp47=fread(FidRead,1,'uint16');                                 %����
%     temp48=fread(FidRead,1,'uint16');                                 %����
%     CircleTotal=fread(FidRead,1,'uint16');			      	%������
    temp5=fread(FidRead,38,'uint8');%����
    R=fread(FidRead,460,'uint8');             %129��588 ��460�ֽڷ���������
    V=fread(FidRead,920,'uint8');             %589��1508 ��920�ֽ��ٶ�����
    W=fread(FidRead,920,'uint8');             %1509��2428 ��920�ֽ��׿�����
    temp6=fread(FidRead,2,'uint16');		  %����
              
    if  length(R)==0
        break  
    end
    %------�ж��Ƿ�����������Ƿ�Χ��------------
    if ElNumber==Ei_input
        
        dBZ=R/2-33;
        VV=V/2-64.5;
        WW=W/2-64.5;
        %-----������ѡ����-------
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
    alpha=0:pi/50:2*pi;%�Ƕ�[0,2*pi]
    x=r*cos(alpha);
    y=r*sin(alpha);
    plot(x,y,'-k')
    axis square
    hold on
end

%������
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
% xlabel('����(km)')
% ylabel('����(km)')
xlabel('km')
ylabel('km')
% title('S�����״�۲�ķ��������ӣ����ݣ�');
% title('Observed reflectivity of LWS','FontSize',13);
axis square

% hold on
% plot(0,0,'r+','markersize',10,'LineWidth',2)
% plot(105*sin(276.5*pi/180),105*cos(276.5*pi/180),'r+','markersize',10,'LineWidth',2)
% % plot(175*sin(259*pi/180),175*cos(259*pi/180),'r+','markersize',10,'LineWidth',2)
% plot(175*sin(259*pi/180),175*cos(259*pi/180),'r+','markersize',10,'LineWidth',2)
% sita=0:pi/1000:2*pi;
% plot(120*cos(sita)+105*sin(276.5*pi/180),120*sin(sita)+105*cos(276.5*pi/180),'b','markersize',10,'LineWidth',1); %�뾶Ϊr��Բ,x0,y0Ϊԭ������
% plot(120*cos(sita)+175*sin(259*pi/180),120*sin(sita)+175*cos(259*pi/180),'b','markersize',10,'LineWidth',1);
% plot(112*sin(122.05*pi/180),112*cos(122.05*pi/180),'r+','markersize',10,'LineWidth',1.5)
% plot(103*sin(163.94*pi/180),103*cos(163.94*pi/180),'r+','markersize',10,'LineWidth',1.5)
% plot(27*sin(162.94*pi/180),27*cos(162.94*pi/180),'r+','markersize',10,'LineWidth',1.5)
% sita=0:pi/1000:2*pi;
% plot(120*cos(sita)+112*sin(122.05*pi/180),120*sin(sita)+112*cos(122.05*pi/180),'k','markersize',10,'LineWidth',1.5); %�뾶Ϊr��Բ,x0,y0Ϊԭ������
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
    alpha=0:pi/50:2*pi;%�Ƕ�[0,2*pi]
    x=r*cos(alpha);
    y=r*sin(alpha);
    plot(x,y,'-k')
    axis square
    hold on
end

%������
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
    alpha=0:pi/50:2*pi;%�Ƕ�[0,2*pi]
    x=r*cos(alpha);
    y=r*sin(alpha);
    plot(x,y,'-k')
    axis square
    hold on
end

%������
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











