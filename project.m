%% TF of ServoMotor
    Gc = tf ([-0.8054,4204,1.444e06],[1, 469.1, 3.676e04,1.356e06]);
%% PID Tuner
    [K,info] = pidtune(Gc,'pid'); 
%% Applying PID tuner on ServoMotor TF    
    s = tf("s");
    Gc2 = Gc*K;
    T1 = feedback(Gc,1);
    T2 = feedback(Gc2,1);
%% Root Locus plot
    %rlocus(T1);
    %rlocus(T2);
%% Finding The Steady State Error

    SP = 12;
    [y,t]=step(T1*SP); 
    sserror=abs(SP-y(end));
    disp("Steady State Error Before PID:");
    disp(sserror);
    
    [y1,t1] = step(T2*SP); 
    sserror1=abs(SP-y1(end));
    disp("Steady State Error After PID:");
    disp(sserror1);
%% Transient Response Parameters 
    disp("Transient Response Before PID:");
    disp(stepinfo(T1));
    disp("Transient Response After PID:");
    disp(stepinfo(T2));
%% Z Transform of PID Control
   syms s;
   pcontrol = (0.0133*s^2+ 2.36*s + 94.3)/s; 
   pZ = ztrans(pcontrol);
%% Total Transfer Function
   T1; % S Domain 
   z = c2d(T1,0.01); % Z Domain
   
   T2;
   z1 = c2d(T2,0.01);
%% Checking The System Stability
   disp("System Stability Before PID:");
   disp(isstable(T1));
   disp("System Stability After PID:");
   disp(isstable(T2));
%% Step Plot with and without PID
    step(T1,'b'); hold on
    step(T2, 'r');
    legend("Before PID", "After PID");