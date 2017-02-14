use std::fs::File;
use std::path::Path;
use std::io::Read;
use std::error::Error;

struct Point {
    x: i32,
    y: i32
}

fn turn<'c>(compass: &str, direction: &str) -> &'c str {
    if compass == "N" && direction == "L" { return "W"; }
    else if compass == "N" && direction == "R" { return "E"; }
    else if compass == "E" && direction == "L" { return "N"; }
    else if compass == "E" && direction == "R" { return "S"; }
    else if compass == "S" && direction == "L" { return "E"; }
    else if compass == "S" && direction == "R" { return "W"; }
    else if compass == "W" && direction == "L" { return "S"; }
    else if compass == "W" && direction == "R" { return "N"; }
    return "N";
}

fn step<'c>(location: &mut Point, compass: &str, blocks: i32) -> Vec<String> {
    let mut rv: Vec<String> = Vec::new();
    match compass {
        "N" => {
            for y in (location.y + 1)..(location.y + blocks + 1) {
                rv.push(format!("{},{}", location.x, y));
            }
            location.y = location.y + blocks;
        },
        "E" => {
            for x in (location.x + 1)..(location.x + blocks + 1) {
                rv.push(format!("{},{}", x, location.y));
            }
            location.x = location.x + blocks;
        },
        "S" => {
            for y in (location.y - blocks)..(location.y) {
                rv.push(format!("{},{}", location.x, y));
            }
            location.y = location.y - blocks;
        },
        "W" => {
            for x in (location.x - blocks)..(location.x) {
                rv.push(format!("{},{}", x, location.y));
            }
            location.x = location.x - blocks;
        },
        _ => {},
    }
    rv
}

fn main() {
    let path = Path::new("input/1.txt");
    let mut file = match File::open(&path) {
        Err(why) => panic!("Couldn't open file {}: {}", path.display(), why.description()),
        Ok(file) => file
    };

    let mut s = String::new();
    match file.read_to_string(&mut s) {
        Err(why) => panic!("Couldn't read file {}: {}", path.display(), why.description()),
        _ => {},
    }
    let mut directions: Vec<&str> = s.split(",").collect();
    directions = directions.iter().map(|d| d.trim()).collect();

    let mut location = Point {x: 0, y: 0};
    let mut locations: Vec<String> = Vec::new();
    locations.push(format!("0,0"));
    let mut compass: &str = "N";
    let mut first_repeat: String = String::new();

    for d in directions {
        let dir: String = d.chars().take(1).collect();
        let blocks: i32 = d.chars().skip(1).collect::<String>().parse().unwrap();
        compass = turn(compass, &dir);
        let steps: Vec<String> = step(&mut location, compass, blocks);
        for s in steps {
            if locations.contains(&s) && first_repeat.is_empty() {
                first_repeat = s.clone();
            }
            locations.push(s);
        }
    }

    println!("1: We've ended up at ({},{})", location.x, location.y);
    println!("2: The first location visited twice was ({})", first_repeat);

}
