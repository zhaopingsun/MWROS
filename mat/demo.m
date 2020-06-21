[fn fp]=uigetfile('*.AR2;*.bin');
fname=strcat(fp,fn);
bd=Fun_Read_MSD_Radar_BaseData(fname);

ci=1;
dbt=Fun_MSD_Radar_BaseData_Select(bd,ci,'dBT');
reso=dbt.Resolution*1.0;
draw_ppi(dbt.Azimuth,reso,dbt.Data');