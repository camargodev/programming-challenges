MID_DAY = '12'
MID_NIGHT = '00'
BEFORE_NOON = 'AM'

def time_conversion(ampm_time):
    hours, minutes, seconds, day_part = calculate_time_parts(ampm_time)
    hours = convert_hours(hours, day_part)
    return "{0}:{1}:{2}".format(hours, minutes, seconds)
    
def calculate_time_parts(ampm_time):
    hours, minutes, seconds_with_suffix = ampm_time.split(":")
    seconds, day_part = seconds_with_suffix[:2], seconds_with_suffix[2:]
    return hours, minutes, seconds, day_part

def convert_hours(hours, day_part):
    if hours == MID_DAY:
        return MID_NIGHT if day_part == BEFORE_NOON else MID_DAY
    return hours if day_part == BEFORE_NOON else str(int(hours)+12)