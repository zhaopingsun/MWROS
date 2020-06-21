function [] = Draw_China_GIS(Radar_Longitude,Radar_Latitude, Display_Range,GISOptions) 
%function [] = Draw_China_GIS(Radar_Longitude,Radar_Latitude,
%Display_Range,Options) 
%绘制中国的城市等GIS数据
%设计者：CJJ
%设计时间：2014年3月5日
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global ChinaMap;  %将ChinaMap设定为全局变量。这样，只需要从文件中读取一次即可，可以大大节约时间
if isempty(ChinaMap)
    load ChinaMap  %载入ChinaMap.mat 。该文件是由GenerateMyMap.m生成的
end

%下面就是加上地理信息的代码
Display_Range_Lon=Display_Range/1e3/50;  %根据雷达的量程，算出经纬度的区间是多少度 。考虑到经度区间随纬度增加而减少，所以这里选用了经度1度表示50km，留了较大的余量

%1.先绘制城市
if GISOptions.City
    %1.1先将城市的经纬度换算到雷达的方位和距离，采用CJJ编写的经纬度->极坐标转换程序
    [TargetAzimuth,TargetDistance,TargetElevation] =LonToPolar(Radar_Longitude,Radar_Latitude, 0, ChinaMap.City.Long,  ChinaMap.City.Lat,0 );
    City.x=TargetDistance .* cosd(90 -TargetAzimuth ) .*cosd(TargetElevation) /1e3; %换算到km
    City.y=TargetDistance .* sind(90 -TargetAzimuth ) .*cosd(TargetElevation) /1e3;

    %1.2选择距离雷达在显示量程范围之内的城市
    if GISOptions.SmallCity
        city_select_index= find( (abs(City.x)< Display_Range/1e3) & (abs(City.y)< Display_Range/1e3)   )  ;  %注意：这里要用 & ，而不是&&
    else
        %如果不需要显示小城市，则不选取Class=4的城市
        city_select_index= find( (ChinaMap.City.Class~=4) &  (abs(City.x)< Display_Range/1e3) & (abs(City.y)< Display_Range/1e3)   )  ;  %注意：这里要用 & ，而不是&&
    end
    city_select.x=City.x(city_select_index);
    city_select.y=City.y(city_select_index);
    city_select.Name=ChinaMap.City.Name(city_select_index);
    city_select.Class=ChinaMap.City.Class(city_select_index);

    %1.3如果大城市和小城市位置很接近，则将小城市去掉
    big_city_select_index=find( (city_select.Class~=4)  )  ;   %先把大城市找出来
    distance_threshold=Display_Range/1e3  /10;  %在距离上相距多少，就不再显示小城市了 。显示量程的1/10
    for ii=big_city_select_index
        for jj=1:length(city_select.Name)  %遍历所有的城市
            if city_select.Class(jj) ~=4 , continue; end
            dx= city_select.x(ii) - city_select.x(jj);
            dy= city_select.y(ii) - city_select.y(jj);
            if (( abs(dx)<distance_threshold) && (abs(dy)<distance_threshold))
                city_select.x(jj)=NaN;
                city_select.y(jj)=NaN;
            end
        end
    end

    %1.4 将城市名字绘制在图上
    hold on
    for ii=1:length(city_select.Name)
        if ((city_select.Class(ii)==1) ||(city_select.Class(ii)==2))
            text(city_select.x(ii),city_select.y(ii),city_select.Name(ii),'fontsize',10) ;
        elseif city_select.Class(ii)==3
            text(city_select.x(ii),city_select.y(ii),city_select.Name(ii),'fontsize',8) ;
        else
            text(city_select.x(ii),city_select.y(ii),city_select.Name(ii),'fontsize',6) ;
        end
    end

end

%%%%%%%%%%%%%%%%%%%%
%2.再绘制省界
if GISOptions.ProvinceBoundaries
    %2.1 先根据雷达的经纬度，预先挑选一下
    Long_diff=abs( ChinaMap.ProvinceBoundaries.Long - Radar_Longitude);
    Lat_diff=abs( ChinaMap.ProvinceBoundaries.Lat - Radar_Latitude);
    GIS_data_select_index_first= find( isnan(Long_diff) | (    (Long_diff < Display_Range_Lon) & (Lat_diff<Display_Range_Lon) ));  %注意：要把NaN的数据保留（因为NaN的数据表示一个线段的结束）

    GIS_data_select_first.Long=ChinaMap.ProvinceBoundaries.Long(GIS_data_select_index_first);
    GIS_data_select_first.Lat=ChinaMap.ProvinceBoundaries.Lat(GIS_data_select_index_first);

    %2.2 将省界的经纬度换算到雷达的方位和距离，采用CJJ编写的经纬度->极坐标转换程序
    [TargetAzimuth,TargetDistance,TargetElevation] =LonToPolar(Radar_Longitude, Radar_Latitude, 0,GIS_data_select_first.Long,  GIS_data_select_first.Lat,0 );
    GIS_data.x=TargetDistance .* cosd(90 -TargetAzimuth ) .*cosd(TargetElevation) /1e3; %换算到km
    GIS_data.y=TargetDistance .* sind(90 -TargetAzimuth ) .*cosd(TargetElevation) /1e3;

    %2.3选择距离雷达在显示量程范围之内的点
    GIS_data_select_index= find(isnan(GIS_data.x) |  ( (abs(GIS_data.x)< Display_Range/1e3) &  (abs(GIS_data.y)< Display_Range/1e3)  )  )  ; %注意：要把NaN的数据保留（因为NaN的数据表示一个线段的结束）
    GIS_data_select.x=GIS_data.x(GIS_data_select_index);
    GIS_data_select.y=GIS_data.y(GIS_data_select_index);

    %2.4显示这些选中的线段
    hold on
    plot(GIS_data_select.x,GIS_data_select.y,'g-','LineWidth',1, 'Color',[0.5 0 0.5 ]);
end

%%%%%%%%%%%%%%%%%%%%
%3.再绘制市界
if GISOptions.CityBoundaries
    %3.1 先根据雷达的经纬度，预先挑选一下
    Long_diff=abs( ChinaMap.CityBoundaries.Long - Radar_Longitude);
    Lat_diff=abs( ChinaMap.CityBoundaries.Lat - Radar_Latitude);
    GIS_data_select_index_first= find( isnan(Long_diff) | (    (Long_diff < Display_Range_Lon) & (Lat_diff<Display_Range_Lon) ));  %注意：要把NaN的数据保留（因为NaN的数据表示一个线段的结束）

    GIS_data_select_first.Long=ChinaMap.CityBoundaries.Long(GIS_data_select_index_first);
    GIS_data_select_first.Lat=ChinaMap.CityBoundaries.Lat(GIS_data_select_index_first);

    %3.2 将市界的经纬度换算到雷达的方位和距离，采用CJJ编写的经纬度->极坐标转换程序
    [TargetAzimuth,TargetDistance,TargetElevation] =LonToPolar(Radar_Longitude,Radar_Latitude, 0, GIS_data_select_first.Long,  GIS_data_select_first.Lat,0 );
    GIS_data.x=TargetDistance .* cosd(90 -TargetAzimuth ) .*cosd(TargetElevation) /1e3; %换算到km
    GIS_data.y=TargetDistance .* sind(90 -TargetAzimuth ) .*cosd(TargetElevation) /1e3;

    %3.3选择距离雷达在显示量程范围之内的点
    GIS_data_select_index= find(isnan(GIS_data.x) |  ( (abs(GIS_data.x)< Display_Range/1e3) &  (abs(GIS_data.y)< Display_Range/1e3)  )  )  ; %注意：要把NaN的数据保留（因为NaN的数据表示一个线段的结束）
    GIS_data_select.x=GIS_data.x(GIS_data_select_index);
    GIS_data_select.y=GIS_data.y(GIS_data_select_index);

    %3.4显示这些选中的线段
    hold on
    plot(GIS_data_select.x,GIS_data_select.y,'g-','LineWidth',1, 'Color',[0.5 0.5 0.5 ]);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%以后有空再编写绘制河流等

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [TargetAzimuth,TargetDistance,TargetElevation] = LonToPolar (RadarLongitude,RadarLatitude,RadarHeight,TargetLongitude,TargetLatitude,TargetHeight)
%用于从两个点的经纬度计算相对的方位、距离、仰角
%注意：计算所采用的公式是绝对精确的，是经过验证的。参见《雷达试验》
%注意：输入参数中，雷达的位置必须是单个数据，而目标的位置允许是一维数组
%设计者：CJJ
%设计时间：2014.3.4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%对输入参数的范围进行判断
if ( (RadarLongitude > 180) || (RadarLongitude < -180))
    disp('雷达的经度值超过了范围（要求在-180~180之间）');
    return;
end

if (( RadarLatitude > 90) || (RadarLatitude < -90))
    disp('雷达的纬度值超过了范围（要求在-90~90之间）');
    return;
end

if (any(TargetLongitude > 180) || any(TargetLongitude < -180))
    disp ('目标的经度值超过了范围（要求在-180~180之间）');
    return;
end

if (any(TargetLatitude > 90) || any(TargetLatitude < -90))
    disp ('目标的纬度值超过了范围（要求在-90~90之间）');
    return;
end

%先定义地球的地理常数
a = 6378137.0; %地球长半径，按WGS-84坐标系，单位：米
b = a * (1 - 1 / 298.257223563);%  地球短半径，单位：米
e = sqrt((a * a - b * b) / (a * a)); % 地球偏心率

B0 = RadarLatitude * pi / 180.0;   %雷达在空间大地坐标中的位置 纬度
L0 = RadarLongitude * pi / 180.0;  %雷达在空间大地坐标中的位置 经度
H0 = RadarHeight;  %雷达在空间大地坐标中的位置 高度

N0 = a / sqrt(1 - e * e * sin(B0) * sin(B0)); %雷达所在位置的卯酉曲率半径

X0 = (N0 + H0) * cos(B0) * cos(L0);     %雷达在空间直角坐标系中的位置
Y0 = (N0 + H0) * cos(B0) * sin(L0);   %雷达在空间直角坐标系中的位置
Z0 = (N0 * (1 - e * e) + H0) * sin(B0);   %雷达在空间直角坐标系中的位置


B1 = TargetLatitude * pi / 180.0;    %目标在空间大地坐标中的位置 纬度
L1 = TargetLongitude * pi / 180.0; %目标在空间大地坐标中的位置 经度
H1 = TargetHeight;  %目标在空间大地坐标中的位置 高度

N1 = a ./ sqrt(1 - e * e .* sin(B1) .* sin(B1)); %目标所在位置的卯酉曲率半径

X1 = (N1 + H1) .* cos(B1) .* cos(L1);    %目标在空间直角坐标系中的位置
Y1 = (N1 + H1) .* cos(B1) .* sin(L1);   %目标在空间直角坐标系中的位置
Z1 = (N1 .* (1 - e * e) + H1) .* sin(B1);    %目标在空间直角坐标系中的位置


%计算雷达与目标之间的相差
dX = X1 - X0;
dY = Y1 - Y0;
dZ = Z1 - Z0;

%进行坐标变换，将空间直角坐标系变换为以雷达所在位置的局部直角坐标系
%转换矩阵为：见《大地测量学》第48页
X = (-sin(B0) * cos(L0) * dX) + (-sin(B0) * sin(L0) * dY) + (cos(B0) * dZ);
Y = (-sin(L0) * dX) + (cos(L0) * dY);
Z = (cos(B0) * cos(L0) * dX) + (cos(B0) * sin(L0) * dY) + (sin(B0) * dZ);

TargetDistance = sqrt(X .* X + Y .* Y + Z .* Z); %计算目标相对于雷达的直线距离（米）
TargetAzimuth = atan2(Y, X) / pi * 180.0; %计算目标相对于雷达的方位（度）
TargetElevation = atan2(Z, sqrt(X .* X + Y .* Y)) / pi * 180.0;  %计算目标相对于雷达的仰角（度）

%下面要将方位转换成雷达坐标系中的方位
TargetAzimuth=mod(TargetAzimuth,360);





