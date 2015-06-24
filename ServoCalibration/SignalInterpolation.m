StepTimeNormal = zeros(115,1);
StepInputNormal = zeros(115,1);
StepOutputNormal = zeros(115,1);
for x = 1:115
    StepTimeNormal(x) = (x-1)*2/114;
    if StepTimeNormal(x) < 0.5
        StepInputNormal(x) = 45;
    else
        StepInputNormal(x) = 135;
    end
    lowpoint = 1;
    highpoint=1;
    while (StepTime(highpoint) < StepTimeNormal(x)) && (highpoint < 115)
        lowpoint = highpoint;
        highpoint = highpoint+1;
    end
    StepOutputNormal(x) = StepOutput(lowpoint) + (StepTimeNormal(x) - StepTime(lowpoint))*(StepOutput(highpoint) - StepOutput(lowpoint))/(StepTime(highpoint) - StepTime(lowpoint));
end
StepCalibratedOutput = (StepOutput - 546.9999)*(-90/204);
StepCalibratedOutputNormal = (StepOutputNormal - 546.9999)*(-90/204);

RampTimeNormal = zeros(155,1);
RampInputNormal = zeros(155,1);
RampOutputNormal = zeros(155,1);
for x = 1:155
    RampTimeNormal(x) = (x-1)*2.675/154;
    if RampTimeNormal(x) < 0.5
        RampInputNormal(x) = 40;
    elseif RampTimeNormal(x) < 1.056
        RampInputNormal(x) = (RampTimeNormal(x) - 0.5)*(180) + 40;
    elseif RampTimeNormal(x) < 1.556
        RampInputNormal(x) = 140;
    elseif RampTimeNormal(x) < 2.112
        RampInputNormal(x) = 140 - (180*(RampTimeNormal(x) - 1.556));
    else
        RampInputNormal(x) = 40;
    end
    lowpoint = 1;
    highpoint = 1;
    while (RampTime(highpoint) < RampTimeNormal(x)) && (highpoint < 155)
        lowpoint = highpoint;
        highpoint = highpoint + 1;
    end
    RampOutputNormal(x) = RampOutput(lowpoint) + (RampTimeNormal(x) - RampTime(lowpoint))*(RampOutput(highpoint) - RampOutput(lowpoint))/(RampTime(highpoint) - RampTime(lowpoint));
end
RampCalibratedOutput = (RampOutput-545.2)*(-100/220.5);
RampCalibratedOutputNormal = (RampOutputNormal-545.2)*(-100/220.5);

SinTimeNormal = zeros(337,1);
SinInputNormal = zeros(337,1);
SinOutputNormal = zeros(337,1);
for x = 1:337
    SinTimeNormal(x) = (x-1)*6/336;
    SinInputNormal(x) = (50*sin(SinTimeNormal(x)*3.14)) + 90;
    lowpoint = 1;
    highpoint = 1;
    while (SinusoidalTime(highpoint) < SinTimeNormal(x)) && (highpoint < 337)
        lowpoint = highpoint;
        highpoint = highpoint + 1;
    end
    SinOutputNormal(x) = SinusoidalOutput(lowpoint) + (SinTimeNormal(x) - SinusoidalTime(lowpoint))*(SinusoidalOutput(highpoint) - SinusoidalOutput(lowpoint))/(SinusoidalTime(highpoint) - SinusoidalTime(lowpoint));
end
SinCalibratedOutput = (SinusoidalOutput-544.2)*(-100/218);
SinCalibratedOutputNormal = (SinOutputNormal-544.2)*(-100/218);