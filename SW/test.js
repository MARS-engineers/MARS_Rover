function enableMotors () {
    send_to_car("0x10010000")
}
input.onButtonPressed(Button.A, function () {
    strip.showColor(neopixel.colors(NeoPixelColors.Red))
    Car_Move("FORWARD", "ff")
    basic.pause(200)
    Car_Move("FORWARD", "50")
    basic.pause(1000)
    Car_Move("BACKWARD", "50")
    basic.pause(1000)
    Car_Move("LEFT_SLIDE", "50")
    basic.pause(1000)
    Car_Move("RIGHT_SLIDE", "50")
    basic.pause(1000)
    Car_Move("ROTATE_CLOCKWISE", "50")
    basic.pause(1000)
    Car_Move("ROTATE_COUNTER_CLOCKWISE", "50")
    basic.pause(1000)
    Car_Move("TURN_LEFT_F", "50")
    strip.showColor(neopixel.colors(NeoPixelColors.Green))
    basic.pause(1000)
    Car_Move("TURN_RIGHT_F", "50")
    basic.pause(1000)
    Car_Move("TURN_LEFT_B", "50")
    basic.pause(1000)
    Car_Move("TURN_RIGHT_B", "50")
    basic.pause(1000)
    Car_Move("ROT_POINT_LEFT_F", "50")
    basic.pause(1000)
    Car_Move("ROT_POINT_RIGHT_F", "50")
    strip.showColor(neopixel.colors(NeoPixelColors.Blue))
    basic.pause(1000)
    Car_Move("ROT_POINT_LEFT_B", "50")
    basic.pause(1000)
    Car_Move("ROT_POINT_RIGHT_B", "50")
    basic.pause(1000)
    Car_Move("SLIDE_DIAG_LEFT_F", "50")
    basic.pause(1000)
    Car_Move("SLIDE_DIAG_RIGHT_F", "50")
    basic.pause(1000)
    Car_Move("SLIDE_DIAG_LEFT_B", "50")
    basic.pause(1000)
    Car_Move("SLIDE_DIAG_RIGHT_B", "50")
    basic.pause(1000)
    Car_Move("STOP", "00")
    strip.clear()
})
function disableMotors () {
    send_to_car("0x10000000")
}
input.onButtonPressed(Button.AB, function () {
    Car_Move("STOP", "00")
    control.reset()
})
input.onButtonPressed(Button.B, function () {
    Car_Move("ROT_POINT_LEFT_F", "50")
    basic.pause(500)
    Car_Move("ROT_POINT_RIGHT_F", "50")
    basic.pause(500)
    Car_Move("ROT_POINT_LEFT_B", "50")
    basic.pause(500)
    Car_Move("ROT_POINT_RIGHT_B", "50")
    basic.pause(500)
    Car_Move("STOP", "00")
})
function Car_Move (direction: string, speed: string) {
    basic.clearScreen()
    msg = "00"
    if (direction == "STOP") {
        basic.showIcon(IconNames.No)
        msg = "00"
    } else if (direction == "FORWARD") {
        basic.showArrow(ArrowNames.North)
        msg = "01"
    } else if (direction == "BACKWARD") {
        basic.showArrow(ArrowNames.South)
        msg = "02"
    } else if (direction == "LEFT_SLIDE") {
        basic.showArrow(ArrowNames.West)
        msg = "03"
    } else if (direction == "RIGHT_SLIDE") {
        basic.showArrow(ArrowNames.East)
        msg = "04"
    } else if (direction == "ROTATE_CLOCKWISE") {
        basic.showLeds(`
            # # . . .
            . # . # .
            # . . . #
            . # . # .
            . . # . .
            `)
        msg = "05"
    } else if (direction == "ROTATE_COUNTER_CLOCKWISE") {
        basic.showLeds(`
            . . . # #
            . # . # .
            # . . . #
            . # . # .
            . . # . .
            `)
        msg = "06"
    } else if (direction == "TURN_LEFT_F") {
        basic.showLeds(`
            . . . . .
            # # . . .
            # . # . .
            . . . # .
            . . . # .
            `)
        msg = "07"
    } else if (direction == "TURN_RIGHT_F") {
        basic.showLeds(`
            . . . . .
            . . . # #
            . . # . #
            . # . . .
            . # . . .
            `)
        msg = "08"
    } else if (direction == "TURN_LEFT_B") {
        basic.showLeds(`
            . . . . .
            # # . . .
            . . # . .
            . . . # .
            . . # # .
            `)
        msg = "09"
    } else if (direction == "TURN_RIGHT_B") {
        basic.showLeds(`
            . . . . .
            . . . # #
            . . # . .
            . # . . .
            . # # . .
            `)
        msg = "0A"
    } else if (direction == "ROT_POINT_LEFT_F") {
        msg = "0B"
    } else if (direction == "ROT_POINT_RIGHT_F") {
        msg = "0C"
    } else if (direction == "ROT_POINT_LEFT_B") {
        msg = "0D"
    } else if (direction == "ROT_POINT_RIGHT_B") {
        msg = "0E"
    } else if (direction == "SLIDE_DIAG_LEFT_F") {
        basic.showArrow(ArrowNames.NorthEast)
        msg = "0F"
    } else if (direction == "SLIDE_DIAG_RIGHT_F") {
        basic.showArrow(ArrowNames.NorthWest)
        msg = "10"
    } else if (direction == "SLIDE_DIAG_LEFT_B") {
        basic.showArrow(ArrowNames.SouthWest)
        msg = "11"
    } else if (direction == "SLIDE_DIAG_RIGHT_B") {
        basic.showArrow(ArrowNames.SouthEast)
        msg = "12"
    } else {
    	
    }
    send_to_car("0x20" + msg + speed + "00")
}
function send_to_car (input2: string) {
    pins.i2cWriteNumber(
    85,
    smarttools.stringToInt(input2),
    NumberFormat.UInt32BE,
    false
    )
}
let msg = ""
let strip: neopixel.Strip = null
basic.pause(1000)
enableMotors()
Car_Move("STOP", "00")
strip = neopixel.create(DigitalPin.P16, 4, NeoPixelMode.RGB)
strip.clear()

