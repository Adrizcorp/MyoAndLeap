%% 
clear all;
clc;


datatxt=fileread('file_myo1');
vectors_emg = strsplit(datatxt,';');
mouse_y = dlmread('file_myo2',',');
mouse_x = dlmread('file_myo3',',');
emg_channels = zeros(8,length(vectors_emg));
counter=1;
real_index=1;
for i=1:length(vectors_emg)
    vectors_emg_sub = strsplit(vectors_emg{1,i},',');
    for j=1:8
        emg_channels(j,real_index)=str2double(vectors_emg_sub{j});
    end
    real_index=real_index+1;
   
end
%%
% for i=1:8
%     emg_channels(i,:)=averaging_filter(abs(emg_channels(i,:)),100);
% 
% end

%% 
for i=1:8
    figure; 
    plot(abs(emg_channels(i,:)));
    title(strcat('EMG ',num2str(i)));
end

%%
figure; 
plot(mouse_y);
title('MOUSE Y');

figure; 
plot(mouse_x);
title('MOUSE X');

%%
na=50;% system order Ay(t)
nb=50;% system order By(t)
nk=1; % delay

uy= abs(emg_channels(7,1:1290));%%canal 7 es y, 
ux= abs(emg_channels(3,1:1290));%%canal 3 es x;

u=uy'/(max(uy));
y=mouse_y(1:1290)'/(max(mouse_y(1:1290)));



%lenght of the SISO
m=length(y);
%% init variables for calculations
theta=zeros(1,na+nb)'; % create a zero vector for the coefficients a and b, 2 for a 2 for b


alpha=1e4; %%init factor
residual=zeros(1,m);
error_v=zeros(1,m);
P=alpha*eye(na+nb); % Covariance Matrix
lambda=1; % Forgetting Factor
lambda_inv=1/lambda; % inverse Forgetting Factor
error=0;
error_n=1;
%% for errors and parameters graphs
coeffs_historial=zeros(na+nb,m);
coeffs_historial_error=zeros(na+nb,m);
%% algorithm
for k=(na+nb):m%%sweeping out y
    %taking the new seeds for the coefficients estimation or observations,
    %2 samples behind
    xt=[];
    for order=1:na,
        xt=[xt -y(k-order)];
    end
    for order=1:nb,
        xt=[xt u(k-order)];
    end
    %% RLS calculations
    x=xt';%x from xT
    %calculating P cvariance matrix
    P=lambda_inv*(P-(P*x*xt*P)/(lambda+xt*P*x));
    %taking the covariance matrix calculate and update the weights (Thetha, which are A(t), and B(t) coeffiecients)
    theta_prev=theta;
    theta=theta-P*x*(xt*theta-y(k));
               %____
                 %|
                 %.-> K(t+1)=P*x=P(t+1)*x(t+1)

    %% save the progress of each coefficients to see the convergence, and
    %error.
    for order=1:na,
        coeffs_historial(order,k)=theta(order);
        coeffs_historial_error(order,k)=abs(coeffs_historial(order,k)-theta_prev(order));
    end
    for order=1:nb,
        coeffs_historial(order+na,k)=theta(order+na);
        coeffs_historial_error(order+na,k)=abs(coeffs_historial(order+na,k)-theta_prev(order+na));
    end

 

end

%% Graph Parameters
texto=[];
figure;
subplot(2,2,1)
for order=1:(na),
    plot(coeffs_historial(order,:));
   % texto= [texto;sprintf('a%d',order)];
    hold on;
end
legend(texto);
xlabel('k')
ylabel('parameter')
texto=[];
subplot(2,2,2)
for order=1:(nb),
    plot(coeffs_historial(order+na,:));
   % texto= [texto;sprintf('b%d',order)];
    hold on;
end
legend(texto);
xlabel('k')
ylabel('parameter')
texto=[];


%% 
figure;
plot(error_v);
%taking out the coeficcients
a=[];
b=[];

for order=1:na,
   a=[a theta(order,1)];
end
for order=1:nb,
   b=[b theta(na+order,1)];
end

u1=u;%copy of the input signal
numerator=b;
denomi=[1 a];
yestimate=dlsim(numerator,denomi,u1);%simulation of a discrete linear system to calculate Y estimated


%% system comparison and verification
A=[1 a];
B=[b];


y_estimated = y;


 for k=(na+nb):m
        % Plant response
        y_estimated(k) = b*u(k-1:-1:k-length(b)) - a*y_estimated(k-1:-1:k-length(a));

 end


figure; 
plot(y);
title('Real Mouse Y vs Estimated Mouse Y');
hold on;
plot(y_estimated);


arx1red=idpoly(A,B,1,1); 
zi=iddata(y,u,0.01); 
compare(zi,arx1red);

figure; 
plot(y_estimated,mouse_y);
title('drawing');
xlim([0 127])
ylim([0 95])

