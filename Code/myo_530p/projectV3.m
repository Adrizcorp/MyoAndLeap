%% 
clear all;
clc;
datatxt=fileread('Pronation_supination/emg_data');
vectors_emg = strsplit(datatxt,';');
roll = dlmread('Pronation_supination/roll_data',',');
emg_channels = zeros(8,length(vectors_emg)-1);
counter=1;
real_index=1;
for i=1:length(vectors_emg)
    vectors_emg_sub = strsplit(vectors_emg{1,i},',');
    for j=1:8
        emg_channels(j,real_index)=str2double(vectors_emg_sub{j});
    end
    real_index=real_index+1;
end
roll=roll(100:end);
 
%% Plotting pitch, Roll and Yaw
figure; 
plot(roll);
title('Roll -  Leap Motion');
u_roll= abs(emg_channels(4,100:end));%% pronation supination
y_roll=roll;

%% Plotting EMG signals
figure; 
plot(u_roll);
title('EMG Channel 4 for Pronation Supination - Rectified');


%% identify system pronation supination
na=50;% system order Ay(t)
nb=50;% system order By(t)
[a_roll,b_roll]=identify_system(u_roll,y_roll,na,nb);

%% verify system pronation supination
figure;
yestimate=dlsim(b_roll,a_roll,u_roll);%simulation of a discrete linear system to calculate Y estimated
plot(yestimate);
hold on;
plot(y_roll);
grid minor
title('Comparison for Forarm Pronation and Supination');
legend('Estimation','Leap Original','Location','northwest')
%hold on;
%plot(u_roll);

%% Hand Extension and Flexion
datatxt=fileread('Extension_flexion_hand/emg_data');
vectors_emg = strsplit(datatxt,';');
pitch = dlmread('Extension_flexion_hand/pitch_data',',');
emg_channels = zeros(8,length(vectors_emg)-1);
counter=1;
real_index=1;
for i=1:length(vectors_emg)
    vectors_emg_sub = strsplit(vectors_emg{1,i},',');
    for j=1:8
        emg_channels(j,real_index)=str2double(vectors_emg_sub{j});
    end
    real_index=real_index+1;
end
pitch=pitch(100:end);
%% plotting LEap
figure; 
plot(pitch(1600:2539));
title('Pitch -  Leap Motion');
u_pitch= abs(emg_channels(1,100:end));%% pronation supination
y_pitch=pitch;
%% Plotting EMG signals
figure; 
plot(u_pitch);
title('EMG Channel 1 for Hand Extension and Flexion - Rectified');

%% identify system hand movement Extension Flexion
na=110;% system order Ay(t)
nb=70;% system order By(t)
[a_pitch,b_pitch]=identify_system(u_pitch(700:end),y_pitch(700:end),na,nb);

%% verify system hand movement Extension Flexion
figure;
yestimate=dlsim(b_pitch,a_pitch,u_pitch(700:end));%simulation of a discrete linear system to calculate Y estimated
plot(yestimate(1500:end));
hold on;
plot(y_pitch(1600:1600+length(yestimate(1500:end))));
grid minor
title('Comparison for Hand Extension and Flexion');
legend('Estimation','Leap Original','Location','northwest')
        
% hold on;
% plot(u_pitch);


%% Forearm Extension and Flexion
datatxt=fileread('Extension_flexion_forearm/emg_data');
vectors_emg = strsplit(datatxt,';');
yaw = dlmread('Extension_flexion_forearm/yaw_data',',');
emg_channels = zeros(8,length(vectors_emg)-1);
counter=1;
real_index=1;
for i=1:length(vectors_emg)
    vectors_emg_sub = strsplit(vectors_emg{1,i},',');
    for j=1:8
        emg_channels(j,real_index)=str2double(vectors_emg_sub{j});
    end
    real_index=real_index+1;
end
yaw=yaw(100:end);
y_yaw=yaw;
figure; 
plot(yaw);
title('Yaw -  Leap Motion');
u_yaw= abs(emg_channels(5,100:end));%% Forearm Extension and Flexion
%% Plotting EMG signals
figure; 
plot(u_yaw);
title('EMG Channel 5 for Forearm Extension and Flexion - Rectified');

%% identify system forearm movement Extension Flexion
na=50;% system order Ay(t)
nb=50;% system order By(t)
[a_yaw,b_yaw]=identify_system(u_yaw,y_yaw,na,nb);
%% verify system hand movement Extension Flexion
figure;
yestimate=dlsim(b_yaw,a_yaw,u_yaw);%simulation of a discrete linear system to calculate Y estimated
plot(yestimate);
hold on;
plot(y_yaw);
grid minor
title('Comparison for Forearm Extension and Flexion');
legend('Estimation','Leap Original','Location','northwest')

