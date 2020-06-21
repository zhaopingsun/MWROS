function [Data] = Fun_Read_MSD_Radar_BaseData(BaseData_File_Name)
%function [Data] =Fun_Read_MSD_Radar_BaseData(BaseData_File_Name)
%从敏视达雷达记录的基数据文件中，读取雷达的各个数据
%先判断Matlab格式的文件是否存在，如果已经存在了，就直接读取matlab格式的文件
%BaseData_File_Name : 文件名
%BaseData :读取的数据，是一个结构
%设计者：CJJ
%设计时间：2014年2月26日
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%先判断Matlab格式的文件是否存在，如果已经存在了，就直接读取matlab格式的文件
% Matlab_MAT_File_Name=[BaseData_File_Name '.mat'];
% if exist(Matlab_MAT_File_Name,'file')
%     fileinfo=dir(BaseData_File_Name);
%     fileinfo_MAT=dir(Matlab_MAT_File_Name);
%      %Mat的文件要比较新，这就可以直接读取matlab格式的文件
%     if fileinfo.datenum<fileinfo_MAT.datenum 
%         load (Matlab_MAT_File_Name)
%         return;
%     end
% end
Data=[];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%然后判断要不要进行解压
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if strcmp(BaseData_File_Name(end-2:end),'bz2')   %说明是压缩文件，要先进行解压
    dos(['bzip2 -d -k -f ' BaseData_File_Name]);
    fid=fopen(BaseData_File_Name(1:end-4)); %打开文件。 注意：要去掉最后的 .bz2
else
    fid=fopen(BaseData_File_Name); %打开文件
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fseek(fid,0,'eof');
BaseData_File_Size_Byte=ftell(fid);
fseek(fid,0,'bof');

%%%%%%%%%%%%%%%%
%1.1.读取32个字节的Generic Header Block
BaseData.Common.Header.MagicWord=  fread(fid,1,'*int32');    %0x4D545352 , Magic word for product
BaseData.Common.Header.MajorVersion=  fread(fid,1,'*int16');    %Major Version
BaseData.Common.Header.MinorVersion=  fread(fid,1,'*int16');    %Minor Version
BaseData.Common.Header.GenericType=  fread(fid,1,'*int32');    %Type of data, see Table 2-3
BaseData.Common.Header.ProductType =  fread(fid,1,'*int32');    %Type  of  Product,  not used for Base Data
BaseData.Common.Header.Reserved =  fread(fid,16,'*uchar');    %Reserved

%1.2.读取128个字节的SITE CONFIG
BaseData.Common.Site.Code =  fread(fid,8,'uint8=>char')';    %Site Code  in characters
BaseData.Common.Site.Name =  fread(fid,32,'uint8=>char')';    %Site Name or  description  in characters
BaseData.Common.Site.Latitude =  fread(fid,1,'*float32');   % Latitude of Radar Site
BaseData.Common.Site.Longitude =  fread(fid,1,'*float32');   % Longitude of Radar Site
BaseData.Common.Site.Height =  fread(fid,1,'*int32');   % Height of  antenna in meters
BaseData.Common.Site.Ground =  fread(fid,1,'*int32');   % Height  of  ground  in meters
BaseData.Common.Site.Frequency =  fread(fid,1,'*float32');   % Radar operation frequency in MHz
BaseData.Common.Site.BeamWidthHori  =  fread(fid,1,'*float32');   % Antenna  Beam  Width Hori
BaseData.Common.Site.BeamWidthVert =  fread(fid,1,'*float32');   % Antenna  Beam  Width Vert
BaseData.Common.Site.Reserved =  fread(fid,60,'*uchar');    %Reserved

%1.3.读取256个字节的TASK CONFIG
BaseData.Common.Task.Name =  fread(fid,32,'uint8=>char')';    %Name of the Task   Configuration
BaseData.Common.Task.Description =  fread(fid,128,'uint8=>char')';    %Description of Task
BaseData.Common.Task.PolarizationType =  fread(fid,1,'*int32');    %Polarization Type: Type  1 - Horizontal 2 - Vertical 3 - Simultaneously 4 - Alternation
BaseData.Common.Task.ScanType =  fread(fid,1,'*int32');    %  Volume Scan Type 0 - PPI Volume Scan 1- Single PPI   2 - Single RHI   3 -Single Sector 4-SectorVolume Scan 5-RHIVolume Scan 6-Manual can
BaseData.Common.Task.PulseWidth =  fread(fid,1,'*int32');    %  Pulse Width ,Nanoseconds
BaseData.Common.Task.VolumeStartTime =  fread(fid,1,'*int32');    %  Start time  of volume scan , UTC , seconds
BaseData.Common.Task.CutNumber =  fread(fid,1,'*int32');    %  Number of Elevation or Azimuth cuts in the task
BaseData.Common.Task.HorizontalNoise =  fread(fid,1,'*float32');    %  Noise  level  of horizontal channel ,dBm
BaseData.Common.Task.VerticalNoise =  fread(fid,1,'*float32');    %  Noise  level  of  vertical channe
BaseData.Common.Task.HorizontalCalibration =  fread(fid,1,'*float32');    %  System  Reflectivity Calibration Const for horizontal channel.
BaseData.Common.Task.VerticalCalibration =  fread(fid,1,'*float32');    %  System  Reflectivity  Calibration Const for vertical channel.
BaseData.Common.Task.HorizontalNoiseTemperature =  fread(fid,1,'*float32');    %  System  Reflectivity Calibration Const for horizontal channel.??? 应该是噪声温度
BaseData.Common.Task.VerticalNoiseTemperature  =  fread(fid,1,'*float32');    %  System  Reflectivity Calibration Const for vertical channel??? 应该是噪声温度
BaseData.Common.Task.ZdrCalibration =  fread(fid,1,'*float32');    %  Reflectivity calibration difference of horizontal  and vertical channel
BaseData.Common.Task.PhaseCalibration =  fread(fid,1,'*float32');    %  Phase calibration  difference of horizontal and vertical channel
BaseData.Common.Task.LDRCalibration =  fread(fid,1,'*float32');    %  LDR calibration difference of horizontal and vertical channel
BaseData.Common.Task.Reserved =  fread(fid,40,'*uchar');    %Reserved

%1.4.读取256*N个字节的CUT CONFIG
for ii=1:BaseData.Common.Task.CutNumber

    BaseData.Common.Cut(ii).ProcessMode =  fread(fid,1,'*int32');    % Main  processing  mode  of signal processing algorithm. 1 - PPP 2 - FFT
    BaseData.Common.Cut(ii).WaveForm =  fread(fid,1,'*int32');       % WSR-88D  defined  wave form  0:CS  1:CD  2:CDX  3:Rx Test  4:BATCH 5:Dual PRF 6:Random Phase 7:SZ
    BaseData.Common.Cut(ii).PRF1 =  fread(fid,1,'*float32');    % Pulse  Repetition  Frequency 1. For wave form Batch  and Dual PRF mode, it is the high PRF, for other modes it is the only PRF.
    BaseData.Common.Cut(ii).PRF2 =  fread(fid,1,'*float32');    % Pulse  Repetition  Frequency 2. For wave form Batch  and Dual PRF mode, it is the low PRF, for other modes it is not used
    BaseData.Common.Cut(ii).UnfoldMode =  fread(fid,1,'*int32');    % Dual PRF mode 1:Single PRF  2: 3:2 mode   3: 4:3 mode    4: 5:4 mode

    BaseData.Common.Cut(ii).Azimuth =  fread(fid,1,'*float32');    % Azimuth degree for RHI scan mode,
    BaseData.Common.Cut(ii).Elevation =  fread(fid,1,'*float32');    % Elevation degree for PPI scan mode
    BaseData.Common.Cut(ii).StartAngle =  fread(fid,1,'*float32');    % Start azimuth angle for  PPI  Sector mode. Start (High) Elevation  for RHI mode.
    BaseData.Common.Cut(ii).EndAngle =  fread(fid,1,'*float32');    % Stop azimuth angle for PPI Sector mode. Stop (Low) Elevation for RHI mode.
    BaseData.Common.Cut(ii).AngleResolution =  fread(fid,1,'*float32');    % Azimuth  resolution  for  PPI  scan, Elevation resolution for RHI mode.
    BaseData.Common.Cut(ii).ScanSpeed =  fread(fid,1,'*float32');    % Azimuth scan speed for PPI scan, Elevation scan speed for RHI mode

    BaseData.Common.Cut(ii).LogResolution =  fread(fid,1,'*int32');    %Range  bin  resolution  for surveillance data, reflectivity and ZDR, etc
    BaseData.Common.Cut(ii).DopplerResolution =  fread(fid,1,'*int32');    %Range bin resolution for  Doppler data, velocity  and spectrum, etc
    BaseData.Common.Cut(ii).MaximumRange =  fread(fid,1,'*int32');    %Maximum range of scan
    BaseData.Common.Cut(ii).MaximumRange2 =  fread(fid,1,'*int32');    %Maximum range of scan
    BaseData.Common.Cut(ii).StartRange =  fread(fid,1,'*int32');    %Start range of scan
    BaseData.Common.Cut(ii).Sample1 =  fread(fid,1,'*int32');    %Pulse sampling number #1. For wave form Batch  and Dual PRF mode, it!s for high PRF, for other modes it!s for only PRF.
    BaseData.Common.Cut(ii).Sample2 =  fread(fid,1,'*int32');    %Pulse sampling number #2. For wave form Batch  and Dual PRF mode, it!s for low PRF, for other modes it!s not used
    BaseData.Common.Cut(ii).PhaseMode =  fread(fid,1,'*int32');    %Phase modulation mode. 1:Fixed Phase  2:Random Phase  3:SZ Phase

    BaseData.Common.Cut(ii).AtmosphericLoss =  fread(fid,1,'*float32');    % two-way  atmospheric  attenuation factor   dB/km
    BaseData.Common.Cut(ii).NyquistSpeed =  fread(fid,1,'*float32');    % m/s

    BaseData.Common.Cut(ii).MomentsMask  =  fread(fid,1,'*uint64');    % Bit  mask  indicates  which moments are involved in the scan. See Table 2-7
    BaseData.Common.Cut(ii).MomentsSizeMask   =  fread(fid,1,'*uint64');    % Bit  mask indicates range  length for  moment data in Table 2-7. 0 for 1 byte, 1 for 2 bytes
    BaseData.Common.Cut(ii).FilterMask   =  fread(fid,1,'*uint32');    %  %注意：这里有问题，感觉要多读4个字节才行，而且MomentsMask 和MomentsSizeMask感觉都不对

    BaseData.Common.Cut(ii).SQIThreshold  =  fread(fid,1,'*float32');    %  SQI Threshold for the scan
    BaseData.Common.Cut(ii).SIGThreshold  =  fread(fid,1,'*float32');    %  SIG Threshold for the scan
    BaseData.Common.Cut(ii).CSRThreshold =  fread(fid,1,'*float32');    %  CSR Threshold for the scan
    BaseData.Common.Cut(ii).LOGThreshold =  fread(fid,1,'*float32');    %  LOG Threshold for the scan
    BaseData.Common.Cut(ii).CPAThreshold =  fread(fid,1,'*float32');    %  CPA Threshold for the scan
    BaseData.Common.Cut(ii).PMIThreshold =  fread(fid,1,'*float32');    %  PMI Threshold for the scan
    BaseData.Common.Cut(ii).ThresholdsReserved =  fread(fid,8,'*uchar');    %Reserved

    BaseData.Common.Cut(ii).dBTMask =  fread(fid,1,'*int32');    %Thresholds used for total reflectivity data. Bits  mask start from "SQI Threshold" take is as LSB.
    BaseData.Common.Cut(ii).dBZMask =  fread(fid,1,'*int32');    %Thresholds used for  reflectivity data. Bits  mask start from "SQI Threshold" take is as LSB.
    BaseData.Common.Cut(ii).VelocityMask =  fread(fid,1,'*int32');    %Thresholds used for  velocity data. Bits  mask start from "SQI Threshold" take is as LSB.
    BaseData.Common.Cut(ii).SpectrumWidthMask =  fread(fid,1,'*int32');    %Thresholds used for  Spectrum  Width data. Bits  mask start from "SQI Threshold" take is as LSB.
    BaseData.Common.Cut(ii).ZDRMask =  fread(fid,1,'*int32');    %Thresholds used for  ZDR data. Bits  mask start from "SQI Threshold" take is as LSB.
    BaseData.Common.Cut(ii).MaskReserved =  fread(fid,12,'*uchar');    %Reserved for mask

    BaseData.Common.Cut(ii).ScanSync =  fread(fid,1,'*int32');    %Reserved
    BaseData.Common.Cut(ii).Direction =  fread(fid,1,'*int32');    %Antenna rotate direction, 1= clockwise, 2=counter clockwise

    BaseData.Common.Cut(ii).GroundClutterClassifierType =  fread(fid,1,'*int16');    %1 - All data is passed   2 - No data is passed 3 Use Real Time GC Classifier  4 use bypassmap
    BaseData.Common.Cut(ii).GroundClutterFilterType =  fread(fid,1,'*int16');    %0- none   1 -Adaptive FFT  4 - IIR
    BaseData.Common.Cut(ii).GroundClutterFilterNotchWidth =  fread(fid,1,'*int16');    %Scaled by 10
    BaseData.Common.Cut(ii).GroundClutterFilterWindow =  fread(fid,1,'*int16');    %-1-none 0 - rect 1-  Hamming 2-  Blackman 3-  Adaptive

    BaseData.Common.Cut(ii).Spare =  fread(fid,72,'*uchar');    %Reserved
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%接下来读取每个径向上的数据
%2 Basedata Radial Data
ii=0;
while(1)
    ii=ii+1;
    %2.1Basedata Radial Header Block
    BaseData.Radial(ii).Header.RadialState= fread(fid,1,'*int32');    %0= Cut Start 1=Intermediate Data 2=Cut End 3=Volume Start 4=Volume End

    BaseData.Radial(ii).Header.SpotBlank= fread(fid,1,'*int32');    %0=Normal 1=Spot Blank
    BaseData.Radial(ii).Header.SequenceNumber= fread(fid,1,'*int32');    %Sequence Number
    BaseData.Radial(ii).Header.RadialNumber= fread(fid,1,'*int32');    %Radial Number for each cut
    BaseData.Radial(ii).Header.ElevationNumber= fread(fid,1,'*int32');    %Elevation Number

    BaseData.Radial(ii).Header.Azimuth= fread(fid,1,'*float32');    %Azimuth Angle
    BaseData.Radial(ii).Header.Elevation= fread(fid,1,'*float32');    %Elevation Angle

    BaseData.Radial(ii).Header.Seconds= fread(fid,1,'*int32');    %Radial data time in second
    BaseData.Radial(ii).Header.microseconds= fread(fid,1,'*int32');    %Radial data time in   microsecond (expect   seconds)
    BaseData.Radial(ii).Header.Lengthofdata= fread(fid,1,'*int32');    %Length of data  in  this radial, this header is excluded
    BaseData.Radial(ii).Header.MomentNumber= fread(fid,1,'*int32');    %Moments available in this radial
    BaseData.Radial(ii).Header.prf= fread(fid,1,'*int16'); 
    BaseData.Radial(ii).Header.Reserved = fread(fid,18,'*uchar');    %

    %2.2 Base Data Moment Header Block
    for jj=1:BaseData.Radial(ii).Header.MomentNumber
        BaseData.Radial(ii).Moment(jj).Header.DataType = fread(fid,1,'*int32');    %Moment data type, See Table 2-7
        BaseData.Radial(ii).Moment(jj).Header.Scale = fread(fid,1,'*int32');    %Data coding scale  Code = value*scale+offset
        BaseData.Radial(ii).Moment(jj).Header.Offset = fread(fid,1,'*int32');    %Data coding offset Code = value*scale+offset

        BaseData.Radial(ii).Moment(jj).Header.BinLength  = fread(fid,1,'*int16');    %Bytes to save each bin of data
        BaseData.Radial(ii).Moment(jj).Header.Flags  = fread(fid,1,'*int16');    %Bit Mask of flags for data. Reserved now

        BaseData.Radial(ii).Moment(jj).Header.Length = fread(fid,1,'*int32');    %Length of data  of  current moment, this header is excluded.

        BaseData.Radial(ii).Moment(jj).Header.Reserved = fread(fid,12,'*uchar');    %

        %2.3 Base Data Moment data
        BaseData.Radial(ii).Moment(jj).Data= fread(fid,double(BaseData.Radial(ii).Moment(jj).Header.Length),'*uchar');
    end

    if ( (BaseData.Radial(ii).Header.RadialState==4) ||  (   (BaseData.Common.Task.ScanType ==2) && (BaseData.Radial(ii).Header.RadialState==2)   )    )   %此时说明体扫结束了！
        break;
    end

    if (   (BaseData.Common.Task.ScanType ==3) && (BaseData.Radial(ii).Header.RadialState==2)    )   %此时说明是PPI扇扫，也结束了！
        break;
    end
    
    if (ftell(fid)==BaseData_File_Size_Byte )  %此时说明体扫结束了！
        disp('注意：这个体扫数据不完整，没有得到RadialState==4的标记，最后一圈的数据丢失了！');
        break;
    end

end

%关闭文件
fclose(fid);

cut_number=BaseData.Common.Task.CutNumber;
if(cut_number>1)
    s = sprintf('数据为VCP扫描,请重新选择数据!');
    msgbox(s);
    return;
end
%2.再依次将各个径向上的数据填入各个cut
for ii=1:BaseData.Common.Task.CutNumber

    %2.1先将这个cut上第一个触发的时间、参数个数、距离库数，就作为这个cut的时间、参数个数、距离库数
    utc_time=double( BaseData.Radial((ii)).Header.Seconds + double(BaseData.Radial((ii)).Header.microseconds)/1e6 );
    Data.Cut(ii).UTC=datestr(datenum(1970,1,1,0,0,0)+  utc_time/86400  ,'dd-mmm-yyyy HH:MM:SS' );

    Data.Cut(ii).MomentNumber=BaseData.Radial((ii)).Header.MomentNumber;    %Moments available in this radial
    Data.Cut(ii).DataLength=zeros(1,Data.Cut(ii).MomentNumber);
    
     for kk=1:Data.Cut(ii).MomentNumber
        binlen= (BaseData.Radial((ii)).Moment(kk).Header.BinLength );
        hdrlen=BaseData.Radial((ii)).Moment(kk).Header.Length;
         Data.Cut(ii).DataLength(kk)= hdrlen/int32(binlen);
     end;
    Data.Cut(ii).Resolution =BaseData.Common.Cut(ii).LogResolution;  %得到距离库的长度，单位：m
    Data.Cut(ii).RadialNumber=length(BaseData.Radial);  %得到这个cut的 Radial Number，即相关脉冲组的总数
   
    %2.2 得到每个cut的每个径向上的方位和仰角
    Data.Cut(ii).Azimuth=zeros(Data.Cut(ii).RadialNumber,1);
    Data.Cut(ii).Elevation=zeros(Data.Cut(ii).RadialNumber,1);
    for jj=1:Data.Cut(ii).RadialNumber
        Data.Cut(ii).Azimuth(jj)=BaseData.Radial(jj).Header.Azimuth;
        Data.Cut(ii).Elevation(jj)=BaseData.Radial(jj).Header.Elevation;
        Data.Cut(ii).prf(jj)=BaseData.Radial(jj).Header.prf;
    end

    %2.3 得到每个cut下的基数据
    for kk=1:Data.Cut(ii).MomentNumber
        Data.Cut(ii).Moment(kk).Data=single(zeros(Data.Cut(ii).DataLength(kk) ,Data.Cut(ii).RadialNumber )); %预先开辟空间
        Data.Cut(ii).Moment(kk).DataType=   BaseData.Radial((ii)).Moment(kk).Header.DataType ;
        switch Data.Cut(ii).Moment(kk).DataType
            case 1
                Data.Cut(ii).Moment(kk).DataTypeString='dBT';
            case 2
                Data.Cut(ii).Moment(kk).DataTypeString='dBZ';
            case 3
                Data.Cut(ii).Moment(kk).DataTypeString='V';
            case 4
                Data.Cut(ii).Moment(kk).DataTypeString='W';
            case 5
                Data.Cut(ii).Moment(kk).DataTypeString='SQI';
            case 6
                Data.Cut(ii).Moment(kk).DataTypeString='CPA';
            case 7
                Data.Cut(ii).Moment(kk).DataTypeString='ZDR';
            case 8
                Data.Cut(ii).Moment(kk).DataTypeString='LDR';
            case 9
                Data.Cut(ii).Moment(kk).DataTypeString='CC';
            case 10
                Data.Cut(ii).Moment(kk).DataTypeString='PHIDP';
            case 11
                Data.Cut(ii).Moment(kk).DataTypeString='KDP';
            case 12
                Data.Cut(ii).Moment(kk).DataTypeString='CP';
            case 13
                Data.Cut(ii).Moment(kk).DataTypeString='FLAG';
            case 14
                Data.Cut(ii).Moment(kk).DataTypeString='HCL';
            case 15
                Data.Cut(ii).Moment(kk).DataTypeString='CF';
            case 16
                Data.Cut(ii).Moment(kk).DataTypeString='SNR';   %注意：根据格式说明文档，这个是ZC，但实际上是SNR
            case 17
                Data.Cut(ii).Moment(kk).DataTypeString='VC';
            case 18
                Data.Cut(ii).Moment(kk).DataTypeString='WC';
            case 19
                Data.Cut(ii).Moment(kk).DataTypeString='PHASE'; %注意：这里比RVP9 输出的多一个“相位”的数据。用于研究大气折射率的变化
            otherwise
                Data.Cut(ii).Moment(kk).DataTypeString='Spare';
        end

        Scale=  double(BaseData.Radial((ii)).Moment(kk).Header.Scale);
        Offset= double( BaseData.Radial((ii)).Moment(kk).Header.Offset);
        BinLength=    BaseData.Radial((ii)).Moment(kk).Header.BinLength;
         xx= Data.Cut(ii).Moment(kk).DataTypeString;
         cut_idex=ii;
        for jj=1:Data.Cut(ii).RadialNumber
            
            
            if BinLength==2
                date_temp=single(BaseData.Radial(jj).Moment(kk).Data(2:2:end)) *256 + single( BaseData.Radial(jj).Moment(kk).Data(1:2:end));
            else
                date_temp=single(BaseData.Radial(jj).Moment(kk).Data);
            end

            date_temp(date_temp==0)=NaN; %将所有的无效数据置为NaN
            Data.Cut(ii).Moment(kk).Data(:,jj)=single((date_temp-Offset)/Scale);
            %rfi=find(date_temp==1);将所有RF数据置为999
            [binnum tmp]=size(date_temp);
            for i=1:binnum
                if(date_temp(i)==1)
                     Data.Cut(ii).Moment(kk).Data(i,jj)=999;
                end;
            end
        end
    end

    %2.4 将一些重要的信息，重新写到Data.Cut 结构中，以方便上层软件使用

    Data.Cut(ii).PRF1= BaseData.Common.Cut(ii).PRF1 ; % Pulse  Repetition  Frequency 1. For wave form Batch  and Dual PRF mode, it is the high PRF, for other modes it is the only PRF.
    Data.Cut(ii).PRF2= BaseData.Common.Cut(ii).PRF2 ; % Pulse  Repetition  Frequency 2. For wave form Batch  and Dual PRF mode, it is the low PRF, for other modes it is not used
    Data.Cut(ii).UnfoldMode=BaseData.Common.Cut(ii).UnfoldMode;    % Dual PRF mode 1:Single PRF  2: 3:2 mode   3: 4:3 mode    4: 5:4 mode

    Data.Cut(ii).RHI_Azimuth =BaseData.Common.Cut(ii).Azimuth;    % Azimuth degree for RHI scan mode,
    Data.Cut(ii).PPI_Elevation =BaseData.Common.Cut(ii).Elevation ;    % Elevation degree for PPI scan mode

    Data.Cut(ii). MaximumRange =BaseData.Common.Cut(ii).MaximumRange ;    %Maximum range of scan
    Data.Cut(ii). Sample1 =BaseData.Common.Cut(ii).Sample1 ;    %Pulse sampling number #1. For wave form Batch  and Dual PRF mode, it!s for high PRF, for other modes it!s for only PRF.
    Data.Cut(ii).Sample2  =BaseData.Common.Cut(ii).Sample2 ;    %Pulse sampling number #2. For wave form Batch  and Dual PRF mode, it!s for low PRF, for other modes it!s not used

    Data.Cut(ii).NyquistSpeed  =BaseData.Common.Cut(ii).NyquistSpeed ;    % m/s
    Data.Cut(ii). LOGThreshold =BaseData.Common.Cut(ii).LOGThreshold ;    %  LOG Threshold for the scan
    Data.Cut(ii). GroundClutterFilterType =BaseData.Common.Cut(ii).GroundClutterFilterType;    %0- none   1 -Adaptive FFT  4 - IIR

    Data.Cut(ii). AngleResolution= BaseData.Common.Cut(ii).AngleResolution ;    % Azimuth  resolution  for  PPI  scan, Elevation resolution for RHI mode.

end
%%%%%%%%%%%%%%%%%%%%%%%%%%
%这里将BaseData的Common下的信息直接赋值到Data
Data.Common=BaseData.Common;
Data.TotalCutNumber=BaseData.Common.Task.CutNumber;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if strcmp(BaseData_File_Name(end-2:end),'bz2')   %说明是压缩文件，要将解压后的文件删除
    delete(BaseData_File_Name(1:end-4));  %将解压后的文件删除
end
%注意：最后，这里将好不容易解开的文件保存起来
% save(Matlab_MAT_File_Name,'Data');



