function [BaseData_Select] = Fun_MSD_Radar_BaseData_Select(BaseData,Cut_Number,Moment_String)
%function [Data] = Fun_MSD_Radar_BaseData_Select(BaseData,Cut_Number,Moment_String)
%从敏视达的基数据中，选取需要的那一层的数据
%设计者：CJJ
%设计时间：2014年2月26日
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Moment_Number=0;
%查找哪一个Moment符合Moment_String
for ii=1:BaseData.Cut(Cut_Number).MomentNumber
    if strcmp(BaseData.Cut(Cut_Number).Moment(ii).DataTypeString,Moment_String)
        Moment_Number=ii;
        break;
    end
end

if Moment_Number==0   %说明没找到了这组参数
    BaseData_Select=[];
    disp(['注意：第' num2str(Cut_Number) '层面没有' Moment_String '的数据'  ]);
    str=['注意：第' num2str(Cut_Number) '层面没有' Moment_String '的数据'];
%     s=sprintf(str);
    msgbox(str);
    return;
else
    %2014.2.27 CJJ将PHIDP的修正去掉了，因为BaseData.Common.Task.PhaseCalibration的用途未明
    %2014.3.2 CJJ又加上了
%     if strcmp( Moment_String,'PHIDP')  %PHIDP要加上修正
%         BaseData_Select.Data=mod( double( BaseData.Cut(Cut_Number).Moment(Moment_Number).Data -BaseData.Common.Task.PhaseCalibration ),360);  %先转换到0~360度之间
% 
%         BaseData_Select.Data(  BaseData_Select.Data >180 ) =BaseData_Select.Data(  BaseData_Select.Data >180 ) -360;   %将凡是>180度的，减去360度，换算到-180~180之间
%     else
%         BaseData_Select.Data=double(BaseData.Cut(Cut_Number).Moment(Moment_Number).Data );
%     end
    BaseData_Select.Data=double(BaseData.Cut(Cut_Number).Moment(Moment_Number).Data );
    %将其他重要的参数也进行赋值
    BaseData_Select.prf=BaseData.Cut(Cut_Number).prf;
    BaseData_Select.UTC=BaseData.Cut(Cut_Number).UTC;
    BaseData_Select.Resolution=double(BaseData.Cut(Cut_Number).Resolution);
    BaseData_Select.DataLength=BaseData.Cut(Cut_Number).DataLength;
    BaseData_Select.RadialNumber= BaseData.Cut(Cut_Number).RadialNumber;

    BaseData_Select.PRF1= BaseData.Cut(Cut_Number).PRF1 ; % Pulse  Repetition  Frequency 1. For wave form Batch  and Dual PRF mode, it is the high PRF, for other modes it is the only PRF.
    BaseData_Select.PRF2= BaseData.Cut(Cut_Number).PRF2 ; % Pulse  Repetition  Frequency 2. For wave form Batch  and Dual PRF mode, it is the low PRF, for other modes it is not used
    BaseData_Select.UnfoldMode=BaseData.Cut(Cut_Number).UnfoldMode;    % Dual PRF mode 1:Single PRF  2: 3:2 mode   3: 4:3 mode    4: 5:4 mode

    BaseData_Select.RHI_Azimuth =BaseData.Cut(Cut_Number).RHI_Azimuth;    % Azimuth degree for RHI scan mode,
    BaseData_Select.PPI_Elevation =BaseData.Cut(Cut_Number).PPI_Elevation ;    % Elevation degree for PPI scan mode

    BaseData_Select. MaximumRange =BaseData.Cut(Cut_Number).MaximumRange ;    %Maximum range of scan
    BaseData_Select. Sample1 =BaseData.Cut(Cut_Number).Sample1 ;    %Pulse sampling number #1. For wave form Batch  and Dual PRF mode, it!s for high PRF, for other modes it!s for only PRF.
    BaseData_Select.Sample2  =BaseData.Cut(Cut_Number).Sample2 ;    %Pulse sampling number #2. For wave form Batch  and Dual PRF mode, it!s for low PRF, for other modes it!s not used

    BaseData_Select.NyquistSpeed  =BaseData.Cut(Cut_Number).NyquistSpeed ;    % m/s
    BaseData_Select. LOGThreshold =BaseData.Cut(Cut_Number).LOGThreshold ;    %  LOG Threshold for the scan
    BaseData_Select. GroundClutterFilterType =BaseData.Cut(Cut_Number).GroundClutterFilterType;    %0- none   1 -Adaptive FFT  4 - IIR

    BaseData_Select. AngleResolution= BaseData.Cut(Cut_Number).AngleResolution ;    % Azimuth  resolution  for  PPI  scan, Elevation resolution for RHI mode.

    BaseData_Select.DataTypeString=BaseData.Cut(Cut_Number).Moment(Moment_Number).DataTypeString;

    BaseData_Select.Azimuth =BaseData.Cut(Cut_Number).Azimuth;    % Azimuth degree for RHI scan mode,
    BaseData_Select.Elevation =BaseData.Cut(Cut_Number).Elevation ;    % Elevation degree for PPI scan mode

    BaseData_Select.SiteName=BaseData.Common.Site.Name;  %Site Name or  description  in characters
    BaseData_Select.Latitude= BaseData.Common.Site.Latitude ;   % Latitude of Radar Site
    BaseData_Select.Longitude=  BaseData.Common.Site.Longitude;   % Longitude of Radar Site
    BaseData_Select.Height=  BaseData.Common.Site.Height  ;  % Height of  antenna in meters
    BaseData_Select.Frequency=  double(BaseData.Common.Site.Frequency )*1e6;   % Radar operation frequency in Hz
    BaseData_Select.BeamWidth=  BaseData.Common.Site.BeamWidthHori;  % Antenna  Beam  Width Hori

    BaseData_Select.TaskName=  BaseData.Common.Task.Name ;    %Name of the Task   Configuration

    BaseData_Select.PolarizationType=BaseData.Common.Task.PolarizationType ;    %Polarization Type: Type  1 - Horizontal 2 - Vertical 3 - Simultaneously 4 - Alternation
    BaseData_Select.ScanType=BaseData.Common.Task.ScanType ;    %  Volume Scan Type 0 - PPI Volume Scan 1- Single PPI   2 - Single RHI   3 -Single Sector 4-SectorVolume Scan 5-RHIVolume Scan 6-Manual can
    BaseData_Select.PulseWidth= double(BaseData.Common.Task.PulseWidth)/1e9 ;    %  Pulse Width , seconds

    BaseData_Select. HorizontalNoise=BaseData.Common.Task.HorizontalNoise ;    %  Noise  level  of horizontal channel ,dBm
    BaseData_Select. VerticalNoise=BaseData.Common.Task.VerticalNoise ;    %  Noise  level  of  vertical channe
    BaseData_Select.HorizontalCalibration= BaseData.Common.Task.HorizontalCalibration ;    %  System  Reflectivity Calibration Const for horizontal channel.
    BaseData_Select.VerticalCalibration= BaseData.Common.Task.VerticalCalibration;    %  System  Reflectivity  Calibration Const for vertical channel.

    BaseData_Select.CutNumber=Cut_Number;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %2014.3.4
    %对方位进行重新排序，以便能按照递增的顺序，也为了今后的方便
%     if ( (BaseData_Select.ScanType==0) ||  (BaseData_Select.ScanType==1) ||  (BaseData_Select.ScanType==3) ||  (BaseData_Select.ScanType==4) )
%         for ii=1:BaseData_Select.RadialNumber-1
%             if ( ( BaseData_Select.Azimuth(ii) > 358) && (BaseData_Select.Azimuth(ii+1)<2) )  %说明此时方位跨越了零度
%                 index_new=[ii+1: BaseData_Select.RadialNumber  1: ii];   %得到新的索引表，以便进行重新排序赋值
% 
%                 %对下面3个与方位有关的数据要同时进行重新排序
%                 BaseData_Select.Azimuth= BaseData_Select.Azimuth(index_new);
%                 BaseData_Select.Elevation= BaseData_Select.Elevation(index_new);
%                 BaseData_Select.Data= BaseData_Select.Data(:,index_new);
%                 break;
%             end
%         end
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %2013.3.7
        BaseData_Select.WaveForm=BaseData.Common.Cut(Cut_Number).WaveForm ;    % WSR-88D  defined  wave form  0:CS  1:CD  2:CDX  3:Rx Test  4:BATCH 5:Dual PRF 6:Random Phase 7:SZ
        %     switch  BaseData_Select.WaveForm
        %         case 2
        %             BaseData_Select.WaveForm_String='CDX';
        %         otherwise
        %             BaseData_Select.WaveForm_String='NONE';
        %     end
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %2014.3.14
        %CJJ发现有时第一个数据的方位并不是接近0度，有时会接近1度，因此这里进行一下判断，如果是接近1度，则将最后一个径向的数据放到第一个来
        %注意：这段功能还需验证
        if ( (BaseData_Select.Azimuth(1)>0.5) && (BaseData_Select.Azimuth(1)<1) )
            index_new=[BaseData_Select.RadialNumber  1: BaseData_Select.RadialNumber-1];   %得到新的索引表，以便进行重新排序赋值
            %对下面3个与方位有关的数据要同时进行重新排序
            BaseData_Select.Azimuth= BaseData_Select.Azimuth(index_new);
            BaseData_Select.Elevation= BaseData_Select.Elevation(index_new);
            BaseData_Select.Data= BaseData_Select.Data(:,index_new);

        end
    end
end




