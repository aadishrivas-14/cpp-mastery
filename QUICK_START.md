# Quick Start Guide

## First Time Setup
```bash
cd /home/eshdiar/cpp/cpp-mastery
python3 update_progress.py status
```

## Resume Learning
```bash
# Check current progress
python3 update_progress.py status

# Get resume guide
python3 update_progress.py resume

# Navigate to current week
cd week-1  # or current week
cat README.md
```

## Track Progress
```bash
# Mark task complete
python3 update_progress.py complete task "Calculator Project"

# Mark theory complete  
python3 update_progress.py complete theory "basics.md"

# Mark project complete
python3 update_progress.py complete project "Banking System"

# Add notes
python3 update_progress.py note "Struggled with memory management"

# Update current position
python3 update_progress.py set 2 3  # Week 2, Day 3
```

## AI Assistant Resume Commands
When you return and want to continue with AI assistance:

```
"Check my C++ mastery progress and help me continue from where I left off"

"I'm back to continue C++ learning, show me my current status"

"Resume my C++ mastery program from the progress tracker"
```

## File Structure
- `PROGRESS_TRACKER.md` - Visual progress overview
- `progress_state.json` - Machine-readable progress data
- `update_progress.py` - Progress management script
- `week-X/README.md` - Week overviews
- `week-X/theory/` - Theory content
- `week-X/projects/` - Project specifications
